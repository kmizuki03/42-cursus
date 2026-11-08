#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <exception>

class Span
{
	private:
		unsigned int		_maxSize;
		std::vector<int>	_numbers;

	public:
		Span();
		Span(unsigned int n);
		Span(const Span &other);
		Span &operator=(const Span &other);
		~Span();

		void			addNumber(int number);
		unsigned int	shortestSpan() const;
		unsigned int	longestSpan() const;

		template <typename InputIterator>
		void	addRange(InputIterator begin, InputIterator end)
		{
			for (InputIterator it = begin; it != end; ++it)
			{
				this->addNumber(*it);
			}
		}

		class SpanFullException : public std::exception
		{
			public:
				SpanFullException();
				SpanFullException(const SpanFullException &other);
				SpanFullException &operator=(const SpanFullException &other);
				virtual ~SpanFullException() throw();

				virtual const char	*what() const throw();
		};

		class NoSpanException : public std::exception
		{
			public:
				NoSpanException();
				NoSpanException(const NoSpanException &other);
				NoSpanException &operator=(const NoSpanException &other);
				virtual ~NoSpanException() throw();

				virtual const char	*what() const throw();
		};
};

#endif
