#ifndef BUS_HPP
#define BUS_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <SystemComponent.hpp>
#include <DataValue.hpp>
#include <list>

class BUS : public SystemComponent
{
	private:
		double width;
		SystemComponent* source;
		//std::string sourceLabel;
		std::list<DataValue> pendingData;
		std::list<DataValue> readyData;
		bool isBinded;
		double counter;
	
	public:
		BUS(const std::string& fileName);
		void simulate() override;
		DataValue read() override;
		std::string getLabelFromSource();
		void bindToSource(SystemComponent* src) override;
};

#endif


