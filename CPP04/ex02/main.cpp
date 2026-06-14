#include "Animal.hpp"
#include "Brain.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main()
{
	std::cout << "=== Test 1: Cannot instantiate Animal (abstract class) ===" << std::endl;
	std::cout << "Animal is abstract - cannot be instantiated directly" << std::endl;

	std::cout << "\n=== Test 2: Can instantiate Dog and Cat ===" << std::endl;
	{
		const Animal* dog = new Dog();
		const Animal* cat = new Cat();

		std::cout << "\nTypes:" << std::endl;
		std::cout << dog->getType() << std::endl;
		std::cout << cat->getType() << std::endl;

		std::cout << "\nSounds:" << std::endl;
		dog->makeSound();
		cat->makeSound();

		std::cout << "\nDeleting:" << std::endl;
		delete dog;
		delete cat;
	}

	std::cout << "\n=== Test 3: Array of Animals ===" << std::endl;
	{
		const int size = 6;
		Animal* animals[size];

		std::cout << "Creating animals:" << std::endl;
		for (int i = 0; i < size; i++)
		{
			if (i < size / 2)
			{
				animals[i] = new Dog();
			}
			else
			{
				animals[i] = new Cat();
			}
		}

		std::cout << "\nMaking sounds:" << std::endl;
		for (int i = 0; i < size; i++)
		{
			std::cout << animals[i]->getType() << ": ";
			animals[i]->makeSound();
		}

		std::cout << "\nDeleting animals:" << std::endl;
		for (int i = 0; i < size; i++)
		{
			delete animals[i];
		}
	}

	std::cout << "\n=== Test 4: Deep copy still works ===" << std::endl;
	{
		Dog dog1;
		dog1.getBrain()->setIdea(0, "I love bones!");

		Dog dog2(dog1);
		std::cout << "\nBrain addresses:" << std::endl;
		std::cout << "dog1: " << dog1.getBrain() << std::endl;
		std::cout << "dog2: " << dog2.getBrain() << std::endl;
		std::cout << "Different? " << (dog1.getBrain() != dog2.getBrain() ? "Yes" : "No") << std::endl;

		std::cout << "\nIdeas:" << std::endl;
		std::cout << "dog1: " << dog1.getBrain()->getIdea(0) << std::endl;
		std::cout << "dog2: " << dog2.getBrain()->getIdea(0) << std::endl;

		dog2.getBrain()->setIdea(0, "I love treats!");
		std::cout << "\nAfter modification:" << std::endl;
		std::cout << "dog1: " << dog1.getBrain()->getIdea(0) << std::endl;
		std::cout << "dog2: " << dog2.getBrain()->getIdea(0) << std::endl;
	}

	std::cout << "\n=== Test 5: Subject test ===" << std::endl;
	{
		const Animal* j = new Dog();
		const Animal* i = new Cat();

		delete j;
		delete i;
	}

	return 0;
}
