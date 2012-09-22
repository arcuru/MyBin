// Implementation of the templated Vector class
#ifdef __VECTOR_H__
#ifndef __VECTOR_CC__
#define __VECTOR_CC__

using namespace std;

// Default constructor
template <typename T>
Vector<T>::Vector()
{
	count = 0;
	reserved = 0;
}

// Copy constructor
template <typename T>
Vector<T>::Vector(const Vector& rhs)
{
	count = rhs.count;
	reserved = rhs.reserved;
	elements = (T*) malloc(reserved * sizeof(T));
	// Copy each element in rhs into this.elements
	for (size_t i = 0; i < count; i++) {
		new (&elements[i]) T(rhs[i]);
	}
}

// Other constructors
template <typename T>
Vector<T>::Vector(size_t nReserved)
{ // Initialize with reserved memory
	count = 0;
	Reserve(nReserved);
}

template <typename T>
Vector<T>::Vector(size_t n, const T& t)
{ // Initialize with "n" copies of "t"
	reserved = n;
	count = n;
	elements = (T*) malloc(reserved * sizeof(T));
	for (size_t i = 0; i < count; i++) {
		new (&elements[i]) T(t);
	}
}

// Reserve memory
template <typename T>
void Vector<T>::Reserve (size_t n)
{
	// Don't do anything if requested reserve size is less than current count
	if (n <= count)
		return;
	T* new_elements = (T*) malloc(n * sizeof(T));
	if (0 != count) {
		// Copy old elements into new memory
		for (size_t i = 0; i < count; i++) {
			new (&new_elements[i]) T(elements[i]);
			elements[i].~T();
		}
	}
	// Free old memory
	if (0 != reserved)
		free(elements);
	// Save newly allocated space to elements
	reserved = n;
	elements = new_elements;
}

// Destructor
template <typename T>
Vector<T>::~Vector()
{
	Clear();
	free(elements);
}

// Add and access front and back
// NOTE. Code for Push_Back included below for a starting point
template <typename T>
void Vector<T>::Push_Back(const T& rhs)
{
	if (reserved > count) { // Already have memory, just add the element
		new (&elements[count]) T(rhs);
	}
	else { // Not enough memory, reallocate
		T* newElements = (T*)malloc((count + 1) * sizeof(T));
		reserved = count + 1;
		// And copy elements to new memory
		for (size_t i = 0; i < count; ++i) {
			new (&newElements[i]) T(elements[i]);
			// And call destructor on the old element
			elements[i].~T();
		}
		// Copy newly pushed element
		new (&newElements[count]) T(rhs);
		// free old memory
		if (count > 0)
			free(elements);
		elements = newElements;
	}
	count++;
}

template <typename T>
void Vector<T>::Push_Front(const T& rhs)
{
	if (reserved > count) { // Already have memory, just add the element
		new (&elements[count]) T();
		for (size_t i = count; i > 0; i--) {
			elements[count] = elements[count-1];
		}
		elements[0] = rhs;
	}
	else { // Not enough memory, reallocate
		T* newElements = (T*)malloc((count + 1) * sizeof(T));
		reserved = count + 1;
		// And copy elements to new memory
		for (size_t i = 0; i < count; ++i) {
			new (&newElements[i+1]) T(elements[i]);
			// And call destructor on the old element
			elements[i].~T();
		}
		// Copy newly pushed element
		new (&newElements[0]) T(rhs);
		// free old memory
		free(elements);
		elements = newElements;
	}
	count++;
}

template <typename T>
void Vector<T>::Pop_Back()
{ // Remove last element
	// Do nothing if count is 0
	if (0 == count)
		return;
	count--;
	elements[count].~T();
}

template <typename T>
void Vector<T>::Pop_Front()
{ // Remove first element
	// Do nothing if count is 0
	if (0 == count)
		return;
	count--;
	// Shift all elements down by one
	for (size_t i = 0; i < count; i++) {
		elements[i].~T();
		new (&elements[i]) T(elements[i+1]);
	}
	elements[count].~T();
}

// Element Access
template <typename T>
T& Vector<T>::Front() const
{
	return elements[0];
}

// Element Access
template <typename T>
T& Vector<T>::Back() const
{
	// Return the same as Front() in case of an empty array
	if (0 == count)
		return elements[0];
	return elements[count-1];
}

template <typename T>
T& Vector<T>::operator[](size_t i) const
{
	return elements[i];
}

template <typename T>
size_t Vector<T>::Size() const
{
	return count;
}

template <typename T>
bool Vector<T>::Empty() const
{
	return (0 == count);
}

// Implement clear
template <typename T>
void Vector<T>::Clear()
{
	while (!Empty())
		Pop_Back();
}

// Iterator access functions
template <typename T>
VectorIterator<T> Vector<T>::Begin() const
{
	return VectorIterator<T>(elements);
}

template <typename T>
VectorIterator<T> Vector<T>::End() const
{
	return VectorIterator<T>(&elements[count]);
}

// Erase and insert
template <typename T>
void Vector<T>::Erase(const VectorIterator<T>& it)
{
	// Calculate the array offset into elements using pointer arithmetic
	size_t offset = it.current - elements;
	count--;
	// Shift elements down by one index
	for (size_t i = offset; i < count; i++) {
		elements[i].~T();
		new (&elements[i]) T(elements[i+1]);
	}
	if (0 != count)
		elements[count].~T();
}

template <typename T>
void Vector<T>::Insert(const T& rhs, const VectorIterator<T>& it)
{
	// Calculate the array offset into elements using pointer arithmetic
	size_t offset = it.current - elements;
	if (reserved > count) { // Already have memory, just add the element
		new (&elements[count]) T();
		for (size_t i = count; i > offset; i--) {
			elements[count] = elements[count-1];
		}
		elements[0] = rhs;
	}
	else { // Not enough memory, reallocate
		T* newElements = (T*)malloc((count + 1) * sizeof(T));
		reserved = count + 1;
		// And copy elements to new memory
		for (size_t i = 0; i < offset; ++i) {
			new (&newElements[i]) T(elements[i]);
			// And call destructor on the old element
			elements[i].~T();
		}
		new (&newElements[offset]) T(rhs);
		for (size_t i = offset; i < count; ++i) {
			new (&newElements[i+1]) T(elements[i]);
			// And call destructor on the old element
			elements[i].~T();
		}
		// free old memory
		free(elements);
		elements = newElements;
	}
	count++;
}

// Implement the iterators

// Constructors
template <typename T>
VectorIterator<T>::VectorIterator()
{
	current = NULL;
}

template <typename T>
VectorIterator<T>::VectorIterator(T* c)
{
	current = c;
}

// Copy constructor
template <typename T>
VectorIterator<T>::VectorIterator(const VectorIterator<T>& rhs)
{
	current = rhs.current;
}

// Iterator defeferencing operator
template <typename T>
T& VectorIterator<T>::operator*() const
{
	return *current;
}

// Prefix increment
template <typename T>
VectorIterator<T>  VectorIterator<T>::operator++()
{
	current++;
	return *this;
}

// Postfix increment
template <typename T>
VectorIterator<T> VectorIterator<T>::operator++(int)
{
	// Create temporary VectorIterator for return value
	VectorIterator tmp(*this);
	++(*this);
	return tmp;
}

// Comparison operators
template <typename T>
bool VectorIterator<T>::operator !=(const VectorIterator<T>& rhs) const
{
	return (current != rhs.current);
}

template <typename T>
bool VectorIterator<T>::operator ==(const VectorIterator<T>& rhs) const
{
	return (current == rhs.current);
}

#endif //__VECTOR_CC__
#endif //__VECTOR_H__

