#ifndef _STACK_H_
#define _STACK_H_

#include <algorithm>
#include <utility>

template <typename T>
class stack
{
public:
	stack() /* noexcept */;
	stack(stack<T> const&) /* strong */;
	stack<T>& operator=(stack<T> const&) /* strong */;
	size_t count() const /* noexcept */;
	void push(T const &) /* strong */;
	void pop() /* strong */;
	T top() const /* strong */;

private:
	void swap(stack<T>&) /* noexcept */;
	T * array_;
	size_t array_size_;
	size_t count_;
};


template <typename T>
stack<T>::stack()
	: count_(0), array_size_(0), array_(nullptr) /* noexcept */
{
}


template <typename T>
void stack<T>::swap(stack<T>& obj) /* noexcept */
{
	using std::swap;

	swap(count_, obj.count_);
	swap(array_size_, obj.array_size_);
	swap(array_, obj.array_);
}

template <typename T>
stack<T>::stack(stack<T> const& other) /* strong */
{
	auto narray = new T[other.array_size_];

	count_ = other.count_;
	array_size_ = other.array_size_;
	array_ = narray;

	std::copy(other.array_, other.array_ + count_, array_);
}


template <typename T>
stack<T>& stack<T>::operator=(stack<T> const& other) /* strong */
{
	if (this != &other)
	{
		stack<T> tmp(other);
		swap(tmp);
	}

	return *this;
}


template <typename T>
size_t stack<T>::count() const /* noexcept */
{
	return count_;
}


template <typename T>
void stack<T>::push(T const& obj)
{
	if (count_ == array_size_)
	{
		auto array_size = array_size_ == 0 ? 1 : array_size_ * 2;
		T* narray = new T[array_size];
		std::copy(array_, array_ + count_, narray);

		array_size_ = array_size;

		if (array_)
			delete[] array_;
		array_ = narray;
	}

	array_[count_] = obj;
	++count_;
}


template <typename T>
T stack<T>::top() const /* strong */
{
	if (count_ == 0)
	{
		throw "Stack is empty!";
	}

	return array_[count_ - 1];
}


template <typename T>
void stack<T>::pop() /* strong */
{
	if (count_ == 0)
	{
		throw "Stack is empty!";
	}

	count_--;
}


#endif
