#include "pch.h"
#include <iostream>

int main()
{
    std::cout << "Hello World!\n"; 


	#ifdef _DEBUG
		std::cout << "Hello U!\n";
	#endif // _DEBUG

}

