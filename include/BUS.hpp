#ifndef BUS_HPP
#define BUS_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <SystemComponent.hpp>
#include <DataValue.hpp>
#include <list>
#include <vector>
class BUS : public SystemComponent
{
	private:
		double width;
		std::vector<DataValue> pendingData;
		std::vector<DataValue> readyData;
		bool isBinded;
		double counter;
	
	public:
		BUS(const std::string& fileName);
		void simulate() override;
		DataValue read() override;
		std::string getLabelFromSource();
		void bindToSource(SystemComponent* src) override;
		// for test
		void getReadyData();
		void getPendingData();
};

#endif


