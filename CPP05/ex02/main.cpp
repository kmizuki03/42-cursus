#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <ctime>
#include <cstdlib>

int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	Bureaucrat	boss("Boss", 1);
	Bureaucrat	intern("Intern", 150);

	ShrubberyCreationForm	shrub("garden");
	RobotomyRequestForm		robot("Bender");
	PresidentialPardonForm	pardon("Marvin");

	std::cout << "--- Unsigned execution attempt ---" << std::endl;
	boss.executeForm(shrub);

	std::cout << "--- Sign and execute by boss ---" << std::endl;
	boss.signForm(shrub);
	boss.executeForm(shrub);

	boss.signForm(robot);
	boss.executeForm(robot);

	boss.signForm(pardon);
	boss.executeForm(pardon);

	std::cout << "--- Low grade execution attempt ---" << std::endl;
	RobotomyRequestForm	robot2("R2D2");
	intern.signForm(robot2);
	boss.signForm(robot2);
	intern.executeForm(robot2);

	return 0;
}
