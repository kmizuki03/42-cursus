#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "Intern.hpp"
#include <ctime>
#include <cstdlib>

int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	Intern		someRandomIntern;
	Bureaucrat	boss("Boss", 1);

	const std::string	requests[3] = {
		"robotomy request",
		"shrubbery creation",
		"presidential pardon"
	};

	for (int i = 0; i < 3; i++)
	{
		AForm	*form = someRandomIntern.makeForm(requests[i], "Bender");
		boss.signForm(*form);
		boss.executeForm(*form);
		delete form;
	}

	std::cout << "--- Unknown form ---" << std::endl;
	try
	{
		AForm	*form = someRandomIntern.makeForm("coffee break", "office");
		delete form;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
