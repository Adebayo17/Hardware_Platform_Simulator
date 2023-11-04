#include <iostream>
#include <string>
#include <DataValue.hpp>


DataValue::DataValue() 
	: value(0.0), valid(false) {}

DataValue::DataValue(double value, bool valid) 
	: value(value), valid(valid) {}


double DataValue::getValue() const {
	return value;
}


bool DataValue::isValid() const {
	return valid;
}


void DataValue::setValue(double newValue) {
	value = newValue;
}


void DataValue::setValid(bool newValid) {
	valid = newValid;
}

void DataValue::readDataValue()
{
	std::cout << "(" << value << "; " << valid << ")";
}

void testDataValue() {
	DataValue data;
	std::cout << "Data : " << data.getValue() << " " << data.isValid() << std::endl;

	data = DataValue(5.5, true);
	std::cout << "Data : " << data.getValue() << " " << data.isValid() << std::endl;

	data.setValue(45.25);
	data.setValid(false);
	std::cout << "Data : " << data.getValue() << " " << data.isValid() << std::endl;

};