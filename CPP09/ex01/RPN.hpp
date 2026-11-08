#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>
#include <list>

class RPN
{
	private:
		std::stack<int, std::list<int> >	_stack;

		bool	applyOperator(char op);

	public:
		RPN();
		RPN(const RPN &other);
		RPN &operator=(const RPN &other);
		~RPN();

		bool	evaluate(const std::string &expression, int &result);
};

#endif
