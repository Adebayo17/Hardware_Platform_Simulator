#include <DISPLAY.hpp>
#include <DataValue.hpp>

DISPLAY::DISPLAY(const std::string& fileName) 
{
	std::ifstream file(fileName); 

	if (!file) {
		std::cerr << "Error : Unable to open MEMORY build file." << std::endl;
	}

	textfile += fileName;
    isBinded = false;
    R = 0;
  
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
            else if (cle == "REFRESH") {
                refresh = std::stoi(valeur);
            }
            else if (cle == "SOURCE") {
                sourceLabel = valeur;
            }
            else {
                std::cerr << "Error : DISPLAY's attribute undefine." << std::endl;
            }
        }
    }
}

std::string DISPLAY::getLabelFromSource()
{
	if(source != nullptr)
    {
        return source->getLabel();
    }
    return "No source bound.";
}


void DISPLAY::bindToSource(SystemComponent* src)
{
    if(src->getLabel() == sourceLabel && (isBinded == false)){
        source = src;
        isBinded = true;
    }
    else {
        std::cerr << "Source is not compatible" << std::endl;
        isBinded = false;
    }
    
}

void DISPLAY::simulate() 
{
    //std::cout << "DISPLAY : " << label << " is simulated." << std::endl;
    if (R == 0) {
        // Réagit une fois sur R
        //std::cout << "Can display " << std::endl; 
        R = refresh;
        DataValue data;
        do {
            data = source->read();
            if (data.isValid()) {
                oldestData = data;
                std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
                std::cout << "++++++     " << data.getValue() << "      +++++" << std::endl;
                std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;  
            }
        } while (data.isValid());    
    }
    else {
        std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
        std::cout << "++     " << oldestData.getValue() << "      ++" << std::endl;
        std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
        R--;
    }
}


DataValue DISPLAY::read()
{
    DataValue data;
    return data;
}
