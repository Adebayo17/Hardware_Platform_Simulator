#ifndef SYSTEM_COMPONENT_HPP
#define SYSTEM_COMPONENT_HPP

#include <iostream>
#include <string>
#include <DataValue.hpp>

class SystemComponent {
	protected:
		std::string type;
		std::string label;
		std::string textfile = CMAKE_SOURCE_DIR;
		std::string sourceLabel;
		SystemComponent* source = nullptr;
	
	public:
		SystemComponent();
		virtual void simulate();
		virtual DataValue read();
		std::string getLabel();
		std::string getType();
		std::string getTextfile();
		std::string getSourceLabel();
		virtual void bindToSource(SystemComponent* src);		
};

#endif