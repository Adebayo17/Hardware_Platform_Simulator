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
    std::cout << "MEMORY : " << label << " is simulated." << std::endl;
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
                    getMemory();
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
    std::cout << "MEMORY : " << label << " is being read at " << memory_ptr << std::endl;
    getMemory();
    if (memoryCount[memory_ptr] < 1) {
        double value = memory[memory_ptr];
        memoryCount[memory_ptr]++;
        std::cout << "Data : --> " << value << " --> " << true << std::endl;
        return DataValue(value, true);
    }
    else {
        std::cout << "Data : --> " << 0.0 << " --> " << false << std::endl;
        return DataValue(0.0, false); // Valeur invalide
    }
    std::cout << std::endl;
}

void MEMORY::getMemory()
{
    std::cout << "Reading memory : " << label << std::endl;
    int i = 0;
    for(double data : memory){
        std::cout << "{ " << data << " ; " << memoryCount[i] << " } | ";
        i++;
    }
    std::cout << std::endl;
}