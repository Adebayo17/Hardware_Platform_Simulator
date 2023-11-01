#include <iostream>
#include <list>
#include <REGISTER.hpp>


// Constructeur
REGISTER::REGISTER() {}

// write in register
void REGISTER::write(double value) {
	registerList.push_back(value);
}

// read from register
double REGISTER::read() {
	if (!isEmpty()) {
		double frontValue = registerList.front();
		registerList.pop_front();
		return frontValue;
	}
	else {
		std::cerr << "Le registre est vide." << std::endl;
		return -1; 
	}
}

// check if register empty
bool REGISTER::isEmpty() {
	return registerList.empty();
}

// size of register
double REGISTER::size() {
	return registerList.size();
}

void REGISTER::getRegister()
{
	for(double data : registerList){
		std::cout << data << "; ";
	}
	std::cout << std::endl;
}

