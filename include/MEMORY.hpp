#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <SystemComponent.hpp>
#include <DataValue.hpp>

class MEMORY : public SystemComponent
{
	private:
		double size;
		double access;
		bool isBinded;
		std::list<double> memory;
		SystemComponent source;
	
	public:
		MEMORY(const std::string& fileName);
    void simulate() override;
    DataValue read() override;
    std::string getLabelFromSource();
    void bind();
};

#endif MEMORY_HPP
