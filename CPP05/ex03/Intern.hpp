#ifndef INTERN_HPP
#define INTERN_HPP

#include <string>
#include <exception>
#include "AForm.hpp"

class Intern
{
	private:
		static AForm	*makeShrubbery(const std::string &target);
		static AForm	*makeRobotomy(const std::string &target);
		static AForm	*makePardon(const std::string &target);

	public:
		Intern();
		Intern(const Intern &other);
		Intern &operator=(const Intern &other);
		~Intern();

		AForm	*makeForm(const std::string &formName, const std::string &target) const;

		class FormNotFoundException : public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};
};

#endif
