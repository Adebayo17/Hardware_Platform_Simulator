#include <iostream>
#include <Hardware_Platform_Simulator.hpp>
#include <DataValue.hpp>
#include <PLATFORM.hpp>

int main() 
{
	//std::cout << "Hello CMake." << std::endl;
	//testDataValue();
	std::string platformFilePath = CMAKE_SOURCE_DIR;
	platformFilePath += "/testdata/platform.txt";
	PLATFORM p1 = PLATFORM(platformFilePath);
	p1.bindComponents();
	p1.simulate();
	return 0;
}