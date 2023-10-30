#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <SystemComponent.hpp>
#include <DataValue.hpp>
#include <list>
#include <vector>

class PLATFORM 
{
    private:
        std::vector<SystemComponent*> components;
        int numberOfComponents;


    public:
        PLATFORM(const std::string& fileName);
        void bindComponents();
        void simulate();
};

#endif