#ifndef QUEUE_HPP
#define QUEUE_HPP

template <class T>
class Queue
{
public:
	virtual ~Queue() {}
	virtual void push_back(const T& e) = 0;
	virtual T front() = 0;
	virtual void pop() = 0;
	virtual bool empty() const = 0;
};

#endif
