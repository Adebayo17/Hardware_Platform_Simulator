#ifndef BUS_HPP
#define BUS_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <SystemComponent.hpp>
#include <DataValue.hpp>

class BUS : public SystemComponent
{
	private:
		double width;
		SystemComponent source;
		std::list<DataValue> pendingData;
		std::list<DataValue> readyData;
		bool isBinded;
		double counter;
	
	public:
		BUS(const std::string& fileName);
    void simulate() override;
    DataValue read() override;
    std::string getLabelFromSource();
    void bind();
};

#endif


