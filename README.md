# Jumputra

A 2D game that involves jumping to the top of a tower.
The longer you hold the spacebar, the higher you will jump (modeled on the game Jump King).
In addition to the classic gameplay, there is also an algorithm visualization available.
Comparison of metaheuristics, machine learning and human performance.

This is part of my master's thesis at Poznan University of Technology:

English: Comparative Analysis of Metaheuristics, Machine Learning, and Human in a Platform Game

Polish: Analiza porównawcza algorytmów metaheurystycznych, uczenia maszynowego i człowieka w grze platformowej

## Build

### CMake
The minimum required version is 3.6. 
```
git clone https://github.com/Putrus/jumputra # Cloning a repository
cd jumputra                                  # Main directory of the cloned repository.
cmake -S . -B build                          # Default compiler
cmake -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE=Release -S . -B build # Recommended g++ compiler
cmake --build build                          # Game installation
```

### Installing required libraries on Ubuntu
```
sudo apt-get install cmake
sudo apt-get install build-essential
sudo apt-get install libx11-dev
sudo apt-get install libxrandr-dev
sudo apt-get install libxinerama-dev
sudo apt-get install libxcursor-dev
sudo apt-get install libgl1-mesa-dev
sudo apt-get install libudev-dev
sudo apt-get install libfreetype-dev
sudo apt-get install libopenal-dev
sudo apt-get install libvorbis-dev
sudo apt-get install libflac-dev
```

## Run
### jumputra
The jumputra executable (jumputra.exe on windows) is located in the build/bin folder

### consolutra
The console version of consolutra (consolutra.exe on windows) simulating the algorithms is also located in the build/bin folder. It should be executed with the parameters.
```
consolutra.exe <properties filename> <world filename> <algorithm name> # Windows
```
