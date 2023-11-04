#include <iostream>
#include <Hardware_Platform_Simulator.hpp>
#include <DataValue.hpp>
#include <PLATFORM.hpp>

int main(int argc, char* argv[]) 
{
	if (argc < 2) {
		std::cerr << "Enter the number of iteration." << std::endl;
		return 1;
	}

	int numIterations = std::atoi(argv[1]);
	
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
	for(int i=0; i<numIterations; i++) {
		//std::cout << std::endl;
		std::cout << i << "****DISPLAY" <<std::endl;
		p1.simulate();
		std::cout << std::endl;
	}
	std::cout << "---------------------------------------------------  END : Simulation             ---------------------------------------------------" <<std::endl;
	return 0;
}