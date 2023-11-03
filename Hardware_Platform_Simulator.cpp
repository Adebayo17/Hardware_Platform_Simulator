#include <iostream>
#include <Hardware_Platform_Simulator.hpp>
#include <DataValue.hpp>
#include <PLATFORM.hpp>

int main() 
{
	std::string platformFilePath = CMAKE_SOURCE_DIR;
	platformFilePath += "/testdata/platform.txt";
	std::cout << "---------------------------------------------------  START : Instantiate PLATFORM ---------------------------------------------------" <<std::endl;
	PLATFORM p1 = PLATFORM(platformFilePath);
	std::cout << "---------------------------------------------------  END   : Instantiate PLATFORM ---------------------------------------------------" <<std::endl;
	std::cout << std::endl;
	std::cout << "---------------------------------------------------  START : Binding Components   ---------------------------------------------------" <<std::endl;
	p1.bindComponents();
	std::cout << "---------------------------------------------------  END   : Binding Components   ---------------------------------------------------" <<std::endl;
	std::cout << std::endl;
	std::cout << "---------------------------------------------------  START : Simulation           ---------------------------------------------------" <<std::endl;
	for(int i=0; i<544; i++) {
		std::cout << std::endl;
		std::cout << i+1 << "-********************SIMULATE" <<std::endl;
		p1.simulate();
	}
	std::cout << "---------------------------------------------------  END : Simulation             ---------------------------------------------------" <<std::endl;
	return 0;
}