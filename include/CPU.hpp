#ifndef CPU_HPP
#define CPU_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <SystemComponent.hpp>
#include <PROGRAM.hpp>
#include <REGISTER.hpp>
#include <DataValue.hpp>

class CPU : public SystemComponent
{
    private:
	    double frequency;
		double F;
	    double cores;
	    Program program;
	    REGISTER cpuRegister;
        double activatedCore;

    public:
	    CPU();
		CPU(const std::string& fileName);
	    void loadProgram();
	    DataValue read() override;
        void simulate() override;
		void activateNextCore();
};

#endif  