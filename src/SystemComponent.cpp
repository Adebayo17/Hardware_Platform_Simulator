#include <iostream>
#include <string>
#include <SystemComponent.hpp>
#include <DataValue.hpp>

SystemComponent::SystemComponent() {}

/*SystemComponent::SystemComponent(std::string type, std::string label, std::string textfile) 
	: type(type), label(label), textfile(textfile) {}
	
SystemComponent::SystemComponent(std::string label) 
	: label(label){}
*/
std::string SystemComponent::getLabel()
{
	return label;
}

std::string SystemComponent::getType()
{
	return type;
}

std::string SystemComponent::getTextfile()
{
	return textfile;
}

std::string SystemComponent::getSourceLabel()
{
	return sourceLabel;
}


void SystemComponent::simulate() {}
DataValue SystemComponent::read() {}
void SystemComponent::bindToSource(SystemComponent* src) {}
