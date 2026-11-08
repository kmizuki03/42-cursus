#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
	try
	{
		Form		taxForm("TaxForm", 50, 25);
		std::cout << taxForm << std::endl;

		Bureaucrat	intern("Intern", 100);
		intern.signForm(taxForm);

		Bureaucrat	manager("Manager", 40);
		manager.signForm(taxForm);
		std::cout << taxForm << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	try
	{
		Form	invalid("Invalid", 0, 50);
		std::cout << invalid << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
