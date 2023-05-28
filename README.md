# OSC Hello-World in CPP

1. [Description](#description)
2. [Dependencies](#dependencies)
3. [How to Install](#how-to-install)
    1. [Copy](#copy)
    2. [Submodule](#submodule)
4. [Run the Examples](#run-the-examples)
    1. [Configure & Generate](#configure--generate)
    2. [Build](#build)
    3. [Run](#run)
5. [Including in your own Project](#including-in-your-own-project)

## Description
Simple Example Programs to send and receive OSC messages using C++ using the OSCPack library and implementing a modern target-based cmake architecture.

## Dependencies
This project depends on the [OSCPack](https://github.com/RossBencina/oscpack/tree/master) library, which is located in the [extern/oscpack](./extern/oscpack/) folder. 
It exports a static library target called OSCPack and can therefore be used in other projects by simply copying over the folder into another cmake project.

## How to install
### Copy
The project can be installed to any location of the installers choice by using the ``git clone --recusive https://github.com/MalteQuandt/OSCPack-Modern`` command somewhere in their own project root, probably a folder like ``extern`` or ``lib``.
### Submodule
In order to use the Project as a submodule, the command ``git submodule add -b main --name oscpack https://github.com/MalteQuandt/OSCPack-Modern <insert_path_here!>`` can be used with the path where the library should be cloned into inserted at the end. 

## Run the Examples
There are two targets to build: 

1. The Client (**OSCPackHelloWorld_Client**)
2. The Server (**OSCPackHelloWorld_Server**)

Replace the \<t> in this guide with the target you would like to construct.

### Configure & Generate
```cmake
cmake -B build -S .
```
You can also configure if the oscpack library should be build either as a static or dynamic library here by passing the ``-DBUILD_SHARED_LIBS=OFF`` for static or ``-DBUILD_SHARED_LIBS=ON`` for dynamic.
If no flags are passed, the library will be build as a static.
### Build
Replace the \<t> here with either **Server** or **Client**.
```cmake
cmake --build build --config Release --target=OSCPackHelloWorld_<t>
```
### Run: 
```cmake
./build/Release/OSCPackHelloWorld_<t>
```

## Including in your Own Project
First, follow the desired step in the [installation](#how-to-install) section of this README. After that step has been completed, the ``add_subdirectory(<relative_path_to_lib>/extern/oscpack)`` command should be included in the root/top level ``CMakeLists.txt`` file of the . When this is done, the library is able to be linked to targets with commands such as ``target_link_libraries``.