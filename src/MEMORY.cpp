#include <MEMORY.hpp>
#include <DataValue.hpp>

MEMORY::MEMORY(const std::string& fileName) 
{
	std::ifstream file(fileName); 

	if (!file) {
		std::cerr << "Error : Unable to open MEMORY build file." << std::endl;
	}

	textfile += fileName;
    isBinded = false;
    memory_ptr = 0;
    A = 0;
  
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
            else if (cle == "SIZE") {
                size = std::stoi(valeur);
                memory.resize(size);
                memoryCount.resize(size, 0);
            }
            else if (cle == "ACCESS") {
                access = std::stoi(valeur);
            }
            else if (cle == "SOURCE") {
                sourceLabel = valeur;
            }
            else {
                std::cerr << "Error : MEMORY's attribute undefine." << std::endl;
            }
        }
    }
}

std::string MEMORY::getLabelFromSource()
{
	if(source != nullptr)
    {
        return source->getLabel();
    }
    return "No source bound.";
}


void MEMORY::bindToSource(SystemComponent* src)
{
    if(src->getLabel() == sourceLabel && (isBinded == false)){
        source = src;
        isBinded = true;
        //std::cout << "SystemComponent: " << label << " ... Source at : " << source << std::endl;
    }
    else {
        std::cerr << "Source is not compatible" << std::endl;
        isBinded = false;
    }
    
}

void MEMORY::simulate() 
{
    if (A == 0) {
            // Réagit une fois sur A
            A = access;
            DataValue data;
            do {
                data = source->read();
                if (data.isValid()) {
                    //writing in the memory
                    memory[memory_ptr] = data.getValue();
                    //initialize the count
                    memoryCount[memory_ptr] = 0;
                    //maj memery_ptr
                    getNextFreeLocation();
                }
            } while (data.isValid());
            
    }
    else {
        A--;
    }
}

void MEMORY::getNextFreeLocation()
{
    memory_ptr = (memory_ptr + 1) % size;
}

DataValue MEMORY::read()
{
    if (memoryCount[memory_ptr] < 1) {
        double value = memory[memory_ptr];
        memoryCount[memory_ptr]++;
        //getNextFreeLocation();
        return DataValue(value, true);
    }
    else {
        return DataValue(0.0, false); // Valeur invalide
    }
}
