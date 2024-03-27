#pragma once
#include <stddef.h>
#include <utility>

#define VECTOR_DEFAULT_CAPACITY 0
#define VECTOR_OUT_OF_BOUND -20

template< typename T>
class Vector {
private:
	T* data_;
	int size_ = 0;
	int capacity_ = VECTOR_DEFAULT_CAPACITY;

public:
	Vector();
	Vector(unsigned int size);
	~Vector();
	void push_back(T&& data);
	int size() const;
	void resize(int size);
	T& operator[](int index);
	const T& operator[](int index) const; 

	Vector(Vector<T>&& other) noexcept;
	Vector<T>& operator=(Vector<T>&& other) noexcept;

	Vector<T> copy() const;

	bool operator==(const Vector<T>& other) const;
};

template< typename T>
bool Vector<T>::operator==(const Vector<T>& other) const {
	if(size_ != other.size_) 
	{
		return false;
	}
	for(int i=0; i<other.size(); i++) 
	{
		if(data_[i] != other[i]) 
		{
			return false;
		}
	}
	return true;
}

template<typename T>
Vector<T> Vector<T>::copy() const {
	Vector<T> newVec(size_);
	for(int i=0; i<size_; ++i) 
	{
		newVec[i] = std::move(data_[i]);
	}
	return newVec;
}

template<typename T>
Vector<T>::Vector(Vector<T>&& other) noexcept {
	data_ = other.data_;
	other.data_ = nullptr;
	size_ = other.size_;
	other.size_ = 0;
	capacity_ = other.capacity_;
	other.capacity_ = 0;
}

template< typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) noexcept{
	std::swap(data_, other.data_);
	std::swap(size_, other.size_);
	std::swap(capacity_, other.capacity_);
	return *this;
}

template< typename T>
Vector<T>::Vector() {
	data_ = new T[capacity_];
}

template< typename T>
Vector<T>::Vector(unsigned int size) {
	capacity_ = 1;
	while (capacity_ < size)
		capacity_ *= 2;
	
	data_ = new T[capacity_];
	size_ = size;
}

template< typename T>
Vector<T>::~Vector() {
	delete[] data_;
}

template< typename T>
void Vector<T>::push_back(T&& value) {
	resize(size() + 1);
	data_[size() - 1] = std::move(value);
}

template< typename T>
int Vector<T>::size() const {
	return size_;
}

template< typename T>
void Vector<T>::resize(int newSize) {
	
	int oldSize = size_;
	size_ = newSize;
	if (size() <= capacity_)
		return;
	if(capacity_ == 0) 
	{
		capacity_ = 1;
	}
	while (size() > capacity_)
	{
		capacity_ *= 2;
	}

	T* newData = new T[capacity_];
	for (int i = 0; i < oldSize; i++)
	{
		newData[i] = std::move(data_[i]);
	}
	delete[] data_;
	data_ = newData;
}

template< typename T>
T& Vector<T>::operator[](int index) {

	if (index >= size() || index < 0)
	{
		throw VECTOR_OUT_OF_BOUND;
	}
	return data_[index];
}

template< typename T>
const T& Vector<T>::operator[](int index) const {

	if (index >= size() || index < 0)
	{
		throw VECTOR_OUT_OF_BOUND;
	}
	return data_[index];
}