#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <functional>
#include <PROGRAM.hpp>


Program::Program() {
	reset();
}

Program::Program(const std::string& fileName) : instructionPointer(0), programPath(fileName) {
	reset();
	loadProgramFromFile();
}

// Charge les instructions � partir d'un fichier
void Program::loadProgramFromFile() {
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
				std::cerr << "Error : Instructions unknown." << std::endl;
			}
			file >> instruction.operand1 >> instruction.operand2;
			instructions.push_back(instruction);
		}
		file.close();
	}
	else {
		std::cerr << "Error : Unable to open PROGRAM build file." << std::endl;
	}
}

// Ex�cute l'instruction courante et avance le pointeur d'instruction
Instruction Program::executeCurrentInstruction() {
	if (instructionPointer < instructions.size()) {
		return instructions[instructionPointer++];
	}
	
}

double Program::executeInstruction() {
	if (instructionPointer < instructions.size()) {
		Instruction instruction = instructions[instructionPointer];
		instruction.result = instruction.operation(instruction.operand1, instruction.operand2);
		instructionPointer++;
		return instruction.result;
	}
	else {
		std::cerr << "Instructions's program terminated." << std::endl;
	}
}

// V�rifie si toutes les instructions ont �t� ex�cut�es
bool Program::allInstructionsExecuted() const {
	return instructionPointer >= instructions.size();
}

// R�initialise le pointeur d'instruction
void Program::reset() {
	instructionPointer = 0;
}


// Définir des fonctions pour chaque instruction
double addition(double a, double b) { return a + b; }
double soustraction(double a, double b) { return a - b; }
double multiplication(double a, double b) { return a * b; }
double division(double a, double b) { return a / b; }
double nop(double a, double b) { return 0; }