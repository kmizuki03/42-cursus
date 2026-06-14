#include "ClapTrap.hpp"

int	main(void)
{
	std::cout << "=== Creating ClapTraps ===" << std::endl;
	ClapTrap clap1("CT-001");
	ClapTrap clap2("CT-002");
	std::cout << "\n=== Basic actions ===" << std::endl;
	clap1.attack("Enemy");
	clap1.takeDamage(5);
	clap1.beRepaired(3);
	std::cout << "\n=== Testing energy depletion ===" << std::endl;
	for (int i = 0; i < 10; i++)
	{
		clap2.attack("Target");
	}
	clap2.attack("Target");
	clap2.beRepaired(5);
	std::cout << "\n=== Testing destruction ===" << std::endl;
	ClapTrap clap3("CT-003");
	clap3.takeDamage(8);
	clap3.takeDamage(5);
	clap3.attack("Enemy");
	clap3.beRepaired(5);
	std::cout << "\n=== Testing copy ===" << std::endl;
	ClapTrap clap4("CT-004");
	ClapTrap clap5(clap4);
	ClapTrap clap6("CT-006");
	clap6 = clap4;
	std::cout << "\n=== Destructors will be called ===" << std::endl;
	return (0);
}
