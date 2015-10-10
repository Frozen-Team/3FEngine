#<div style="text-align:center">3FEngine</div>
## [TODOs](https://github.com/Frozen-Team/3FEngine/blob/master/TODO.md),  [Changelog](https://github.com/Frozen-Team/3FEngine/blob/master/CHANGELOG.md) and Roadmap
## Dependencies
### C\C++ Libraries
    - SDL
    - EntityX
    - RapidJSON
    - cppformat
    - easyloggingpp
    - Eigen
    - FBX SDK
### Software
    - CMake

## How to get started 
1) Clone repository:

    git clone https://github.com/Frozen-Team/3FEngine.git
    cd 3FEngine
    git submodule update --init --recursive
2) Download [FBX SDK](http://usa.autodesk.com/adsk/servlet/pc/item?id=24746731&siteID=123112).  
3) Install FBX SDK. You can intsall it to either $ENGINE_ROOT/3dparty/install folder or custom path.  
4) If FBX SDK installed outside of 3dparty/install folder, you should set environment variable FBXSDK_ROOT, the path to the library root folder.  

To set variable in Windows type in cmd:

    setx FBXSDK_ROOT "Your_FBX_SDK_path_here"

5) Run $ENGINE_ROOT/3dparty/make_all.bat to build 3dparty libraries. You can do this step manually (step 5a).  
x86-64 architecture set by default. In order to change architecture change generator type in make_all.bat to either "Visual Studio 14 2015" or "Visual Studio 14 2015 Win64" for x86 or x86-64 respectively.  
6) Generate the solution for 3FEngine from root directory after successful build of libs.  
**Limitation**:
The solution can be generated for only one architecture: either x86 or x86-64.  

5a) Go to 3dparty directory and generate solution using CMake. Build a whole solution in both Debug and Release configurations. After each build make the install step (build INSTALL project).

**CMake Generator Visual Studio supported only for now.**

## Documentation
You will need the doxygen tool to generate documentation. Install it, and set environment variable DOXYGEN_EXECUTABLE that point to Doxygen`s binary directory.