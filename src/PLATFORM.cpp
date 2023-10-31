#include <PLATFORM.hpp>
#include <DataValue.hpp>
#include <SystemComponent.hpp>
#include <MEMORY.hpp>
#include <CPU.hpp>
#include <BUS.hpp>
#include <DISPLAY.hpp>
#include <PROGRAM.hpp>
#include <REGISTER.hpp>
#include <filesystem>

PLATFORM::PLATFORM(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "Error(from PLATFORM.cpp): Unable to open PLATFORM build file." << std::endl;
        return;
    }

    std::string componentFilePath;
    while (std::getline(file, componentFilePath)) {
        // Utilisez std::filesystem pour construire le chemin complet
        std::filesystem::path fullComponentPath = std::filesystem::path(CMAKE_SOURCE_DIR) / componentFilePath;

        // Convertissez le chemin complet en chaîne de caractères
        componentFilePath = fullComponentPath.string();
        
        std::cout << componentFilePath << std::endl;
        
        std::ifstream componentFile(componentFilePath);
        if (!componentFile) {
            std::cerr << "Error(from PLATFORM.cpp): Unable to open component file: " << componentFilePath << std::endl;
            continue;
        }

        std::string line;
        std::string componentType;
        while (std::getline(componentFile, line)) {
            std::istringstream lineStream(line);
            std::string cle, valeur;

            if (std::getline(lineStream, cle, ':') && std::getline(lineStream, valeur)) {
                cle.erase(0, cle.find_first_not_of(" \t"));
                cle.erase(cle.find_last_not_of(" \t") + 1);
                valeur.erase(0, valeur.find_first_not_of(" \t"));
                valeur.erase(valeur.find_last_not_of(" \t") + 1);

                if (cle == "TYPE") {
                    componentType = valeur;
                    break; // Nous avons trouvé le type, sortons de la boucle
                }
            }
        }

        SystemComponent* component = nullptr;
        
        if (componentType == "BUS") {
            component = new BUS(componentFilePath);
        }
        else if (componentType == "MEMORY") {
            component = new MEMORY(componentFilePath);
        }
        else if (componentType == "CPU") {
            component = new CPU(componentFilePath);
        }
        else if (componentType == "DISPLAY") {
            component = new DISPLAY(componentFilePath);
        }
        else {
            std::cerr << "Error(from PLATFORM.cpp): SystemComponent unknown " << std::endl;
        }
        // Ajoutez d'autres conditions pour les autres types de composants

        if (component) {
            components.push_back(component);
        }
    }

    numberOfComponents = components.size();
}

void PLATFORM::bindComponents()
{
    for (SystemComponent* component : components) {
        std::string sourceLabel = component->getSourceLabel(); // Obtenez le label de la source du composant
        if (!sourceLabel.empty()) {
            // Recherchez le composant cible avec le label correspondant
            for (SystemComponent* targetComponent : components) {
                if (targetComponent->getLabel() == sourceLabel) {
                    component->bindToSource(targetComponent);
                    std::cout << "SystemComponent: " << component->getLabel() << " ... at " << component << " ... Source to bind is : " << targetComponent->getLabel() << " ... at " << targetComponent << std::endl;
                    break; // Nous avons trouvé la source, sortons de la boucle
                }
            }
        }
    }
}

void PLATFORM::simulate() {
    // Demandez à tous les composants de simuler
    for (SystemComponent* component : components) {
        component->simulate();
    }
}

