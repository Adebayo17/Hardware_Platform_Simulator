#include <MEMORY.hpp>
#include <DataValue.hpp>

MEMORY::MEMORY(const std::string& fileName) 
{
  //initialis� les cores et activ� le premier
	std::ifstream file(fileName); 

	if (!file) {
		std::cerr << "Error : Unable to open CPU build file." << std::endl;
	}

	textfile = fileName;
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
          else if (cle == "SIZE") {
              size = std::stoi(valeur);
          }
          else if (cle == "ACCESS") {
              access = std::stoi(valeur);
          }
          else if (cle == "SOURCE") {
              source = SystemComponent(valeur);
          }
          else {
              std::cerr << "Error : MEMORY's attribute undefine." << std::endl;
          }
      }
  }
}

std::string MEMORY::getLabelFromSource()
{
	return source.getLabel();
}
