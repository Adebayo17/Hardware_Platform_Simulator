#ifndef DATA_VALUE_HPP
#define DATA_VALUE_HPP

#include <iostream>
#include <string>

class DataValue {
	private:
		double value;
		bool valid;
	
	public:
		//constructor
		DataValue();
		DataValue(double value, bool valid);
		
		//getter
		double getValue() const;
		bool isValid() const;
		
		//setter
		void setValue(double newValue);
		void setValid(bool newValid);
		void readDataValue();
};

// TEST
void testDataValue();


#endif