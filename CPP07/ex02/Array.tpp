#ifndef ARRAY_TPP
#define ARRAY_TPP

#include "Array.hpp"

template <typename T>
Array<T>::Array() : _data(new T[0]()), _size(0)
{
}

template <typename T>
Array<T>::Array(unsigned int n) : _data(new T[n]()), _size(n)
{
}

template <typename T>
Array<T>::Array(const Array &other) : _data(new T[other._size]()), _size(other._size)
{
	for (unsigned int i = 0; i < this->_size; i++)
	{
		this->_data[i] = other._data[i];
	}
}

template <typename T>
Array<T> &Array<T>::operator=(const Array &other)
{
	if (this != &other)
	{
		delete[] this->_data;
		this->_size = other._size;
		this->_data = new T[other._size]();
		for (unsigned int i = 0; i < this->_size; i++)
		{
			this->_data[i] = other._data[i];
		}
	}
	return *this;
}

template <typename T>
Array<T>::~Array()
{
	delete[] this->_data;
}

template <typename T>
T &Array<T>::operator[](unsigned int index)
{
	if (index >= this->_size)
	{
		throw OutOfBoundsException();
	}
	return this->_data[index];
}

template <typename T>
const T &Array<T>::operator[](unsigned int index) const
{
	if (index >= this->_size)
	{
		throw OutOfBoundsException();
	}
	return this->_data[index];
}

template <typename T>
unsigned int Array<T>::size() const
{
	return this->_size;
}

template <typename T>
const char *Array<T>::OutOfBoundsException::what() const throw()
{
	return "Array index out of bounds!";
}

#endif
