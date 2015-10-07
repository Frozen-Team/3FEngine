#<div style="text-align:center">3D Game Engine</div>

In order to begin work: 
 
    git clone https://github.com/Frozen-Team/3DEngine.git
    cd 3DEngine
    git submodule update --init --recursive

## How to get started
### Visual Studio 
First of all, go to 3dparty directory and generate solution using CMake. Build a whole solution in both Debug and Release configurations. After each build make the install step (build INSTALL project).

Generate the solution for 3D Engine after successful build of libs.

**Limitation**:
The solution can be generated for only one architecture: either x86 or x86-64.


## Dependencies
### SDL

## Documentation
You will need the doxygen tool to generate documentation. Install it, and set environment variable DOXYGEN_EXECUTABLE that point to Doxygen`s binary directory.

## Found problems
--Cannot build shared version of sdl

## TODO
Linux build