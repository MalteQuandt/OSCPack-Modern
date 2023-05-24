# OSC Hello-World in CPP
## Description
Simple Example Programs to send and receive OSC messages using C++

## Dependencies
This project depends on the [OSCPack](https://github.com/RossBencina/oscpack/tree/master) library, which is located in the [extern/oscpack](./extern/oscpack/) folder. 
It exports a static library target called OSCPack and can therefore be used in other projects by simply copying over the folder into another cmake project.

## How to Run
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