#include "ThreadManager.h"
#include <cassert>

using namespace std;

//#define NDEBUG

struct task_t {
	void *(*task_func) (void *);
	void* input;
};

ThreadManager::ThreadManager()
{
}

ThreadManager::~ThreadManager()
{
}

void ThreadManager::SubmitTask ( void *(*task) (void *), void* input )
{
	if ( nullptr == task )
		return;
	task_t tmp = {task, input};
	task_list.push_back( tmp );
}

void ThreadManager::SubmitThread ( void *(*task) (void *), void* input )
{
	if ( nullptr == task )
		return;
	pthread_t tmp;
	pthread_create( &tmp, nullptr, task, input );
	thread_list.push_back( tmp );
}

inline size_t ThreadManager::GetTaskCount ( ) const
{
	return task_list.size();
}

inline size_t ThreadManager::GetWorkerCount ( ) const
{
	return worker_list.size();
}

inline size_t ThreadManager::GetThreadCount ( )
{
	PruneThreads();
	return thread_list.size();
}

/** PruneThreads
 *  removes threads from thread_list if they are finished
 */
void ThreadManager::PruneThreads ( )
{
	vector<pthread_t>::iterator i;
	for (i = thread_list.begin(); i != thread_list.end(); ++i ) {
		if ( !pthread_tryjoin_np( *i, nullptr ) ) {
			// Successfully finished
			// remove from vector
			thread_list.erase(i);
		}
	}
}

typedef struct {
	pthread_cond_t cond;
	pthread_mutex_t mut1;
	pthread_mutex_t mut2;
	vector<task_t>* tasks;
} WorkerThread_t;

/** WorkerThread
 *  runs constantly in the background, processing tasks in task_list.
 *  If task_list is empty, waits until signaled by master thread
 *  
 *  @arg input Unused input
 *  @return Unused output
 */
void* WorkerThread ( void* input )
{
	WorkerThread_t h = *(WorkerThread_t*)input;
	pthread_cond_t worker_cond = h.cond;
	pthread_mutex_t worker_mutex = h.mut1;
	pthread_mutex_t task_mutex = h.mut2;
	vector<task_t>* task_list = h.tasks;
	delete (WorkerThread_t*)input;
	while ( true ) {
		task_t mytask;
		// Check for free task
		pthread_mutex_lock( &task_mutex );
		// This should only every loop twice
#ifdef NDEBUG
		while ( true ) {
#else
		for (int i = 2; i > 0; --i) {
#endif
			if ( 0 != task_list->size() ) {
				mytask = *task_list->begin();
				task_list->erase( task_list->begin() );
				break;
			}
			else
				pthread_cond_wait( &worker_cond, &task_mutex );
			assert( 1 != i ); // Make sure it only runs around twice
		}
		pthread_mutex_unlock( &task_mutex );

		// Run task
		mytask.task_func( mytask.input );
	}
}

/** Create Workers
 *  creates the specified number of worker threads.
 *
 *  @arg worker_count Number of workers to create
 */
void ThreadManager::CreateWorkers ( size_t worker_count )
{
	for (size_t i = 0; i < worker_count; ++i) {
		pthread_t tmp;
		WorkerThread_t* h = new WorkerThread_t;
		h->cond = worker_cond;
		h->mut1 = worker_mutex;
		h->mut2 = task_mutex;
		h->tasks = &task_list;
		pthread_create( &tmp, nullptr, &WorkerThread, h );
		worker_list.push_back( tmp );
	}
	assert( worker_count == worker_list.size() );
}

