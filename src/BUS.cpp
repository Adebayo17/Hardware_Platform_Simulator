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
    }
    else {
        std::cerr << "(from BUS.cpp) Source is not compatible" << std::endl;
        isBinded = false;
    }
    
}


void BUS::simulate()
{
    //std::cout << "BUS : " << label << " is simulated." << std::endl;
	if(isBinded) {
        //getPendingData();
        //getReadyData();
        //std::cout << "Moving data... " << std::endl;
        for (auto it = pendingData.begin(); it != pendingData.end(); ) {
            readyData.push_back(std::move(*it));
            it = pendingData.erase(it);
        }
        //getPendingData();
        //getReadyData();

        //std::cout << "BUS : " << label << " Reading data from source : " << sourceLabel << std::endl;
        for(double i=0; i<width; i++) {
            //std::cout << i+1 << "-read" <<std::endl; 
            DataValue data;
            data = source->read();
            if(data.isValid()) {
                pendingData.push_back(data);
                //getPendingData();
            }
            else {
                std::cerr << "Error(from BUS.cpp) : Invalid Data read from source : " << sourceLabel << std::endl;
                break;
            }  
        }
        //getPendingData();
        //getReadyData();
    } else {
        std::cerr << "(from BUS.cpp) No source bound." << std::endl;
    }
	
}

DataValue BUS::read()
{
	//std::cout << "BUS : " << label << " is being read" << std::endl;
    //getReadyData();
    DataValue data;
	if(!readyData.empty()) {
        //std::cout << "After reading : " << std::endl;
		data = readyData.front();
		readyData.erase(readyData.begin());
		counter++;
        //getReadyData();
		return data;
	}
	else {
		data = DataValue();	//default ctor (0.0, false)
		return data;
	}
}

void BUS::getPendingData()
{
    std::cout << "Pending data : " << std::endl; 
    for(DataValue data : pendingData){
		std::cout << data.getValue() << " " << data.isValid() << "; " << std::endl;
	}
	std::cout << std::endl;
}

void BUS::getReadyData()
{
    std::cout << "Ready data : " << std::endl;
    for(DataValue data : readyData){
		std::cout << "Value : " << data.getValue() << " ; Flag : " << data.isValid() << "; " << std::endl;
	}
	std::cout << std::endl;
}

