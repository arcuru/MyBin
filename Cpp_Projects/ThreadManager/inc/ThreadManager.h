#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <cstdint>
#include <vector>
#include <pthread.h>

struct task_t;

class ThreadManager
{
	public:
		ThreadManager();
		~ThreadManager();

		void SubmitTask ( void *(*task) (void *), void* input );
		void SubmitThread ( void *(*task) (void *), void* input );

		inline size_t GetTaskCount ( ) const;
		inline size_t GetWorkerCount ( ) const;
		inline size_t GetThreadCount ( );

	private:
		void PruneThreads ( );
		void CreateWorkers ( size_t worker_count );

		std::vector<pthread_t> thread_list; //!< Vector of thread threads
		std::vector<pthread_t> worker_list; //!< Vector of worker threads
		std::vector<task_t> task_list; //!< Vector of tasks to be completed

		pthread_cond_t worker_cond;
		pthread_mutex_t worker_mutex;
		pthread_mutex_t task_mutex;
};

#endif /* THREADMANAGER_H */

