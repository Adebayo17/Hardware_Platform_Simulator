#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <CPU.hpp>
#include <SystemComponent.hpp>
#include <PROGRAM.hpp>
#include <REGISTER.hpp>
#include <DataValue.hpp>

CPU::CPU() {}


CPU::CPU(const std::string& fileName) {
    //initialis� les cores et activ� le premier
	std::ifstream file(fileName); 

	if (!file) {
		std::cerr << "Error(from CPU.cpp) : Unable to open CPU build file." << std::endl;
	}

	textfile += fileName;
    activatedCore = 1;
    F = 0;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string cle, valeur;

        if (std::getline(lineStream, cle, ':') && std::getline(lineStream, valeur)) {
            cle.erase(0, cle.find_first_not_of(" \t"));
            cle.erase(cle.find_last_not_of(" \t") + 1);
            valeur.erase(0, valeur.find_first_not_of(" \t"));
            valeur.erase(valeur.find_last_not_of(" \t") + 1);

            if (cle == "TYPE") {
                type = valeur;
            }
            else if (cle == "LABEL") {
                label = valeur;
            }
            else if (cle == "CORES") {
                cores = std::stoi(valeur);
            }
            else if (cle == "FREQUENCY") {
                frequency = std::stoi(valeur);
            }
            else if (cle == "PROGRAM") {
                program = Program(valeur);
            }
            else if (cle == "SOURCE") {
                sourceLabel = valeur;
            }
            else {
                std::cerr << "Error(from CPU.cpp) : CPU's attribute undefine." << std::endl;
            }
        }
    }
}

void CPU::simulate() {
    double instructionResult;
    for(int i=0; i < frequency; i++)
    {
        if(program.allInstructionsExecuted()) {
            if(activatedCore < cores) {
                activateNextCore();
                program.reset();
                instructionResult = program.executeInstruction();
                cpuRegister.write(instructionResult);
            } else {
                std::cout << "Program terminated from " << label << std::endl;
                return;
            }
        } else {
            instructionResult = program.executeInstruction();
            cpuRegister.write(instructionResult);
        }
    }
}

void CPU::loadProgram()
{
    program.loadProgramFromFile();
}

DataValue CPU::read()
{
	DataValue data;
	if(!cpuRegister.isEmpty()) {
		data = DataValue(cpuRegister.read(), true);
        std::cout << data.getValue() << data.isValid() << std::endl;
		return data;
	}
	else {
		data = DataValue();	//default ctor (0.0, false)
		return data;
	}
}

void CPU::activateNextCore()
{
    activatedCore++;
}

