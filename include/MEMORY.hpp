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
		std::vector<double> memory;
		SystemComponent* source;
		//std::string sourceLabel;
		int memory_ptr;
	
	public:
		MEMORY(const std::string& fileName);
		void simulate() override;
		DataValue read() override;
		std::string getLabelFromSource();
		void bindToSource(SystemComponent* src) override;
		void getNextFreeLocation();
};

#endif
