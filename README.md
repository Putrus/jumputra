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

### Windows
```
git clone https://github.com/Putrus/jumputra
```
```
cd jumputra
```
```
git submodule update --init --recursive
```
```
vcpkg/bootstrap-vcpkg.bat
```

### MSVC x64 Release
```
cmake --preset=msvc-x64
```
```
cmake --build --preset=msvc-x64-release
```

### MinGW x64 g++
```
cmake --preset=gcc-windows-x64
```
```
cmake --build --preset=gcc-windows-x64-release
```

## Run
### jumputra
The jumputra executable (jumputra.exe on windows) is located in the build/${presetName}/bin folder

### consolutra
The console version of consolutra (consolutra.exe on windows) simulating the algorithms is also located in the build/${presetName}/bin folder. It should be executed with the parameters.
```
consolutra.exe -run <properties filename> <world filename> <algorithm name> <max execution minutes>
```
