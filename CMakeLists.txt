# Fichier CMake
# Autor : Gaël BOYA
# Project : Abstraction model of hardware platform
# Date : 18 october 2023

cmake_minimum_required (VERSION 3.12)

project ("Hardware_Platform_Simulator")

# Définition des sources et des exécutables
set(SOURCES
    Hardware_Platform_Simulator.cpp
    src/CPU.cpp
    src/DataValue.cpp
    src/PROGRAM.cpp
    src/REGISTER.cpp
    src/SystemComponent.cpp
)

# Définition des fichiers d'en-tête
set(HEADERS
    include/Hardware_Platform_Simulator.hpp
    include/CPU.hpp
    include/DataValue.hpp
    include/PROGRAM.hpp
    include/REGISTER.hpp
    include/SystemComponent.hpp
)

# Ajouter l'exécutable
add_executable(Hardware_Platform_Simulator ${SOURCES} ${HEADERS})


# Ajout des repertoires du projet
target_include_directories(Hardware_Platform_Simulator PRIVATE "include")
target_include_directories(Hardware_Platform_Simulator PRIVATE "src")
target_include_directories(Hardware_Platform_Simulator PRIVATE "testdata")


# Vous pouvez ajouter d'autres configurations ici, par exemple des options de compilation, des bibliothèques, etc.

# Option pour le répertoire de sortie de l'exécutable
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Indiquez que le fichier Hardware_Platform_Simulator.cpp contient la fonction main
set_target_properties(Hardware_Platform_Simulator PROPERTIES OUTPUT_NAME "Hardware_Platform_Simulator")
