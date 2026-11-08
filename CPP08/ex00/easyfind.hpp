#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm>
#include <exception>

class NotFoundException : public std::exception
{
	public:
		NotFoundException();
		NotFoundException(const NotFoundException &other);
		NotFoundException &operator=(const NotFoundException &other);
		virtual ~NotFoundException() throw();

		virtual const char	*what() const throw();
};

template <typename T>
typename T::iterator	easyfind(T &container, int value)
{
	typename T::iterator	it = std::find(container.begin(), container.end(), value);

	if (it == container.end())
	{
		throw NotFoundException();
	}
	return it;
}

#endif
