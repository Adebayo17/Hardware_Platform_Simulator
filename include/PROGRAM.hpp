#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <functional>

// Enumération des types d'instructions possibles
enum InstructionType {
    ADD,
    SUB, 
    MUL,
    DIV,
    NOP
};

// Déclarer un type de pointeur de fonction pour les opérations
using OperationFunction = double (*)(double, double);

// Définir des fonctions pour chaque instruction
double addition(double a, double b);
double soustraction(double a, double b);
double multiplication(double a, double b);
double division(double a, double b);
double nop(double a, double b);


// Structure pour représenter une instruction
struct Instruction {
    InstructionType type;
    OperationFunction operation;
    double operand1;
    double operand2;
    double result;
};

class Program {
    private:
        std::vector<Instruction> instructions;
        size_t instructionPointer;
        std::string programPath;

    public:
        Program();
        Program(const std::string& fileName);
		void loadProgramFromFile();
		Instruction executeCurrentInstruction();
		double executeInstruction();
		bool allInstructionsExecuted() const;
		void reset();
        void printProgramInstruction();
};

#endif