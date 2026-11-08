#include "Serializer.hpp"
#include <iostream>

int main()
{
	Data		data;
	data.id = 42;
	data.name = "Marvin";
	data.value = 3.14;

	Data		*original = &data;
	uintptr_t	raw = Serializer::serialize(original);
	Data		*restored = Serializer::deserialize(raw);

	std::cout << "Original pointer:  " << original << std::endl;
	std::cout << "Serialized value:  " << raw << std::endl;
	std::cout << "Deserialized ptr:  " << restored << std::endl;

	if (original == restored)
	{
		std::cout << "Success: pointers are equal." << std::endl;
		std::cout << "id:    " << restored->id << std::endl;
		std::cout << "name:  " << restored->name << std::endl;
		std::cout << "value: " << restored->value << std::endl;
	}
	else
	{
		std::cout << "Failure: pointers differ." << std::endl;
	}

	return 0;
}
