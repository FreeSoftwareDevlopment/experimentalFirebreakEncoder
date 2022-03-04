#include <iostream>
#include <fstream>
#include "../firebreak/firebreak.h"

int main()
{
	std::cout << "START" << std::endl;
	Cfirebreak fire;
	bool ex = 1, bex = 0;
	int a = 189,
		a2 = 831;
	fire.AddBool(&ex);
	fire.AddBool(&bex);
	//fire.AddInt(&a);
	//fire.AddInt(&a2);
	size_t buffersize = 0;
	//! WARNING: If you had before a buffer created with the same Cfirebreak , this will be freed before makeBuffer creates a new!
	char* b = fire.makeBuffer(&buffersize);
	std::cout << "CREATED BUFFER\n" << (b != nullptr ? "OK" : "ERR") << std::endl;
	if (b == nullptr)
		return -1;
	std::ofstream of("data.hex", std::ios::out | std::ios::binary);
	if (!of) {
		std::cerr << "Cannot open file!" << std::endl;
		return -1;
	}
	of.write((char*)b, buffersize);
	of.close();
	std::cout << "CREATED FILE\n";
	//freeBuffer optional, the destructor runs it also
	fire.freeBuffer();
}
