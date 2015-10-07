## 3D Game Engine

Get it: 
   git clone https://github.com/Frozen-Team/3DEngine.git
   cd 3DEngine
   git submodule init
   git submodule update --init --recursive

## How to get started
### Visual Studio 
First of all go to 3dparty directory and generate solution using CMake. Build hole solution in both, Debug and Release configurations. After each build make install step (build INSTALL project).

Generate solution for 3D Engine after successfully build of libs.

Limitation:
Solution can be generated for only one architecture, x86 or x86-64.


## Dependencies
### SDL

## Documentation
You will need doxygen tool to generate documentation. Install it and set environment variable DOXYGEN_EXECUTABLE that point to TODO

## Found problems
--Cannot build shared version of sdl

## TODO
Linux build