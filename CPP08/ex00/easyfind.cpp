#include "easyfind.hpp"

NotFoundException::NotFoundException()
{
}

NotFoundException::NotFoundException(const NotFoundException &other) : std::exception(other)
{
}

NotFoundException &NotFoundException::operator=(const NotFoundException &other)
{
	if (this != &other)
	{
		std::exception::operator=(other);
	}
	return *this;
}

NotFoundException::~NotFoundException() throw()
{
}

const char *NotFoundException::what() const throw()
{
	return "Value not found in container!";
}
