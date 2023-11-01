#ifndef REGISTER_HPP
#define REGISTER_HPP

#include <iostream>
#include <list>
#include <vector>

class REGISTER {
    private:
        std::list<double> registerList;

    public:
        // Constructeur
        REGISTER();

        // write in register
        void write(double value);

        // read from register
        double read();

        // check if register empty
        bool isEmpty();

        // size of register
        double size();

        void getRegister();
};

#endif