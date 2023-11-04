#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <SystemComponent.hpp>
#include <DataValue.hpp>
#include <list>
#include <vector>

class MEMORY : public SystemComponent
{
	private:
		int size;
		int access;
		int A;
		bool isBinded;
		std::vector<DataValue> memory;
		std::vector<int> memoryCount;
		int memory_ptr;
		int oldest_value;
	
	public:
		MEMORY(const std::string& fileName);
		void simulate() override;
		DataValue read() override;
		std::string getLabelFromSource();
		void bindToSource(SystemComponent* src) override;
		void getNextFreeLocation();
		void getOldestValue();
		// for test
		void getMemory();
};

#endif
