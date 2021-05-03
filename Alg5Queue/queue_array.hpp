#ifndef QUEUE_ARRAY_HPP
#define QUEUE_ARRAY_HPP

#include "queue.hpp"
#include "exceptions.hpp"

template <typename T>
class QueueArray final: public Queue<T>
{
public:
	QueueArray(size_t size) :
		front_(0),
		back_(0),
		size_(size + 1)
	{
		try
		{
			array_ = new T[size_];
		}
		catch (const std::exception&)
		{
			throw WrongQueueSize();
		}
	}
	QueueArray(const QueueArray<T>& src) = delete;
	QueueArray(QueueArray<T>&& src); 
	QueueArray<T>& operator= (QueueArray<T>&& src);
	virtual ~QueueArray() override { delete[] array_; }
	void push_back(const T& e) override; // next to be written
	T front() override;
	void pop() override;
	bool empty() const override;

private:
	T* array_;
	size_t front_;
	size_t back_;
	size_t size_;
	friend void swap(QueueArray<T>& right);
};

template <typename T>
QueueArray<T>::QueueArray(QueueArray<T>&& src)
{
	QueueArray<T> temp();
	swap(temp, src);
	swap(temp, &this);
}

template <typename T>
QueueArray<T>& QueueArray<T>::operator= (QueueArray<T>&& src)
{
	QueueArray<T> temp();
	swap(temp, src);
	swap(temp, &this);
}

template <typename T>
void QueueArray<T>::push_back(const T& e)
{
	if (front_ - back_ == 1 || back_ - front_ == size_ - 1)
	{
		throw QueueOverflow();
	}
	array_[back_] = e;
	back_ = (back_ + 1) % size_; // both ascending 
}

template <typename T>
T QueueArray<T>::front()
{
	if (front_ == back_)
	{
		throw QueueUnderflow();
	}
	return array_[front_];
}

template <typename T>
void QueueArray<T>::pop()
{
	if (front_ == back_)
	{
		throw QueueUnderflow();
	}
	front_ = (front_ + 1) % size_;
}

template <typename T>
bool QueueArray<T>::empty() const
{
	return front_ == back_;
}

template <typename T>
void swap(QueueArray<T>& left, QueueArray<T>& right)
{
	std::swap(left.array_, right.array_);
	std::swap(left.front_, right.front_);
	std::swap(left.back_, right.back_);
	std::swap(left.size_, right.size_);
}

#endif