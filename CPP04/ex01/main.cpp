#include "Animal.hpp"
#include "Brain.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main()
{
	std::cout << "=== Test 1: Basic creation and deletion ===" << std::endl;
	{
		const Animal* dog = new Dog();
		const Animal* cat = new Cat();

		delete dog;
		delete cat;
	}

	std::cout << "\n=== Test 2: Deep copy with copy constructor ===" << std::endl;
	{
		Dog dog1;
		dog1.getBrain()->setIdea(0, "I love bones!");
		dog1.getBrain()->setIdea(1, "Chase the cat!");

		std::cout << "\nCreating dog2 as copy of dog1:" << std::endl;
		Dog dog2(dog1);

		std::cout << "\nBrain addresses:" << std::endl;
		std::cout << "dog1 brain: " << dog1.getBrain() << std::endl;
		std::cout << "dog2 brain: " << dog2.getBrain() << std::endl;
		std::cout << "Different brains? " << (dog1.getBrain() != dog2.getBrain() ? "Yes" : "No") << std::endl;

		std::cout << "\nIdeas before modification:" << std::endl;
		std::cout << "dog1 idea[0]: " << dog1.getBrain()->getIdea(0) << std::endl;
		std::cout << "dog2 idea[0]: " << dog2.getBrain()->getIdea(0) << std::endl;

		std::cout << "\nModifying dog2's brain:" << std::endl;
		dog2.getBrain()->setIdea(0, "I love treats!");

		std::cout << "dog1 idea[0]: " << dog1.getBrain()->getIdea(0) << std::endl;
		std::cout << "dog2 idea[0]: " << dog2.getBrain()->getIdea(0) << std::endl;
	}

	std::cout << "\n=== Test 3: Deep copy with assignment operator ===" << std::endl;
	{
		Cat cat1;
		cat1.getBrain()->setIdea(0, "I love fish!");

		Cat cat2;
		cat2.getBrain()->setIdea(0, "I love mice!");

		std::cout << "\nBefore assignment:" << std::endl;
		std::cout << "cat1 idea[0]: " << cat1.getBrain()->getIdea(0) << std::endl;
		std::cout << "cat2 idea[0]: " << cat2.getBrain()->getIdea(0) << std::endl;

		std::cout << "\nAssigning cat1 to cat2:" << std::endl;
		cat2 = cat1;

		std::cout << "\nAfter assignment:" << std::endl;
		std::cout << "cat1 brain: " << cat1.getBrain() << std::endl;
		std::cout << "cat2 brain: " << cat2.getBrain() << std::endl;
		std::cout << "cat1 idea[0]: " << cat1.getBrain()->getIdea(0) << std::endl;
		std::cout << "cat2 idea[0]: " << cat2.getBrain()->getIdea(0) << std::endl;

		std::cout << "\nModifying cat2:" << std::endl;
		cat2.getBrain()->setIdea(0, "I love birds!");
		std::cout << "cat1 idea[0]: " << cat1.getBrain()->getIdea(0) << std::endl;
		std::cout << "cat2 idea[0]: " << cat2.getBrain()->getIdea(0) << std::endl;
	}

	std::cout << "\n=== Test 4: Array of Animals ===" << std::endl;
	{
		const int size = 6;
		Animal* animals[size];

		std::cout << "Creating animals:" << std::endl;
		for (int i = 0; i < size; i++)
		{
			if (i < size / 2)
			{
				std::cout << "Creating Dog " << i << std::endl;
				animals[i] = new Dog();
			}
			else
			{
				std::cout << "Creating Cat " << i << std::endl;
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
			std::cout << "Deleting " << animals[i]->getType() << " " << i << std::endl;
			delete animals[i];
		}
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
