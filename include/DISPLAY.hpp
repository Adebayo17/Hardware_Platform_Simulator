#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <SystemComponent.hpp>
#include <DataValue.hpp>
#include <list>
#include <vector>

class DISPLAY : public SystemComponent
{
    private:
        int refresh;
        SystemComponent* source;
        bool isBinded;
        int R;

    public:
        DISPLAY(const std::string& fileName);
		void simulate() override;
		DataValue read() override;
		std::string getLabelFromSource();
		void bindToSource(SystemComponent* src) override;
};

#endif