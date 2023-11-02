#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <functional>
#include <PROGRAM.hpp>
#include <filesystem>


Program::Program() {
	reset();
}

Program::Program(const std::string& fileName) : instructionPointer(0), programPath(fileName) {
	reset();
	loadProgramFromFile();
}

// load instructions from file
void Program::loadProgramFromFile() {
	// Utilisez std::filesystem pour construire le chemin complet
	std::filesystem::path fullComponentPath = std::filesystem::path(CMAKE_SOURCE_DIR) / programPath;

	// Convertissez le chemin complet en chaîne de caractères
	programPath = fullComponentPath.string();
	
	//print program path
	//std::cout << programPath << std::endl;
	
	std::ifstream file(programPath);
	if (file.is_open()) {
		std::string instructionStr;
		while (file >> instructionStr) {
			Instruction instruction;
			if (instructionStr == "ADD") {
				instruction.type = ADD;
				instruction.operation = addition;
			}
			else if (instructionStr == "SUB") {
				instruction.type = SUB;
				instruction.operation = soustraction;
			}
			else if (instructionStr == "MUL") {
				instruction.type = MUL;
				instruction.operation = multiplication;
			}
			else if (instructionStr == "DIV") {
				instruction.type = DIV;
				instruction.operation = division;
			}
			else if (instructionStr == "NOP") {
				instruction.type = NOP;
				instruction.operation = nop;
			}
			else {
				std::cerr << "Error(from PROGRAM.cpp) : Instructions unknown." << std::endl;
			}
			file >> instruction.operand1 >> instruction.operand2;
			instructions.push_back(instruction);
		}
		file.close();
	}
	else {
		std::cerr << "Error(from PROGRAM.cpp) : Unable to open PROGRAM build file." << std::endl;
	}
}

// Execute current instruction courante and incremente le pointeur d'instruction
/*Instruction Program::executeCurrentInstruction() {
	if (instructionPointer < instructions.size()) {
		return instructions[instructionPointer++];
	}
	else {
		return {
			NOP,
			nop,
			0.0,
			0.0,
			0.0
		};
	}
}*/

double Program::executeInstruction() {
	if (instructionPointer < instructions.size()) {
		Instruction instruction = instructions[instructionPointer];
		instruction.result = instruction.operation(instruction.operand1, instruction.operand2);
		instructionPointer++;
		return instruction.result;
	}
	else {
		std::cerr << "(from PROGRAM.cpp) Instructions's program terminated." << std::endl;
		return NULL;
	}
}

// Verify if all instructions are executed
bool Program::allInstructionsExecuted() const {
	return instructionPointer >= instructions.size();
}

// Reinitialise le pointeur d'instruction
void Program::reset() {
	instructionPointer = 0;
}

void Program::printProgramInstruction()
{
	Instruction instr = instructions[instructionPointer];
	std::cout << instr.type << " " << instr.operation << " " << instr.operand1 << " " << instr.operand2 << " --> " << instr.result << std::endl;
}

// Définir des fonctions pour chaque instruction
double addition(double a, double b) 
{ 
	return a + b; 
}
double soustraction(double a, double b) 
{ 
	return a - b; 
}
double multiplication(double a, double b) 
{ 
	return a * b; 
}
double division(double a, double b) 
{ 
	if (b != 0) {
        return a / b;
    } else {
        std::cerr << "Erreur : Division par zéro." << std::endl;
        return 0.0;
    } 
}
double nop(double a, double b) 
{ 
	return 0; 
}