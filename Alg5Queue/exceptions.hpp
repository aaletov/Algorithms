#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>

class QueueOverflow: public std::exception
{
public:
	QueueOverflow():
		std::exception("Queue Overflow")
	{}
};

class QueueUnderflow: public std::exception
{
public:
	QueueUnderflow() :
		std::exception("Queue Underflow")
	{}
};


class WrongQueueSize: public std::exception
{
public:
	WrongQueueSize():
		std::exception("Wrong Queue Size")
	{}

};

#endif