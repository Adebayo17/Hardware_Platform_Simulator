#include <iostream>
#include <BUS.hpp>


BUS::BUS(const std::string& fileName) 
{
	std::ifstream file(fileName); 

	if (!file) {
		std::cerr << "Error(from BUS.cpp) : Unable to open BUS build file." << std::endl;
	}

	textfile += fileName;
    isBinded = false;
    counter = 0;
  
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
            else if (cle == "WIDTH") {
                width = std::stoi(valeur);
            }
            else if (cle == "SOURCE") {
                sourceLabel = valeur;
                
            }
            else {
                std::cerr << "Error(from BUS.cpp) : BUS's attribute undefine." << std::endl;
            }
        }
    }
}

std::string BUS::getLabelFromSource()
{
	if(source != nullptr)
    {
        return source->getLabel();
    }
    return "(from BUS.cpp) No source bound.";
}


void BUS::bindToSource(SystemComponent* src)
{
    if(src->getLabel() == sourceLabel && (isBinded == false)){
        source = src;
        isBinded = true;
        //std::cout << "SystemComponent: " << label << " ... Source at : " << source << std::endl;
    }
    else {
        std::cerr << "(from BUS.cpp) Source is not compatible" << std::endl;
        isBinded = false;
    }
    
}


void BUS::simulate()
{
	if(isBinded) {
        for (DataValue data : pendingData) {
            readyData.push_back(data);
            pendingData.pop_front();
        }
        for(double i=0; i<width; i++) {
            DataValue data;
            data = source->read();
            if(data.isValid()) {
                pendingData.push_back(data);
            }
            else {
                std::cerr << "Error(from BUS.cpp) : Invalid Data read from source : " << sourceLabel << std::endl;
                break;
            }  
        }
    } else {
        std::cerr << "(from BUS.cpp) No source bound." << std::endl;
    }
	
}

DataValue BUS::read()
{
	DataValue data;
	if(!readyData.empty()) {
		data = readyData.front();
		readyData.pop_front();
		counter++;
		return data;
	}
	else {
		data = DataValue();	//default ctor (0.0, false)
		return data;
	}
}



