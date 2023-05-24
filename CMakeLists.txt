cmake_minimum_required(VERSION 3.25)
project(OSCPackHelloWorld
    VERSION
        1.0
    LANGUAGES
        CXX
    DESCRIPTION
        "Simple Client & Server Program to send OSC with CPP using the OSCPack library"
)


# add libraries
add_subdirectory(extern)

## example client
add_executable(${PROJECT_NAME}_Client client-main.cpp)
target_link_libraries(${PROJECT_NAME}_Client PUBLIC OSCPack)
target_compile_features(${PROJECT_NAME}_Client PUBLIC cxx_std_11)

## example server
add_executable(${PROJECT_NAME}_Server server-main.cpp)
target_link_libraries(${PROJECT_NAME}_Server PUBLIC OSCPack)
target_compile_features(${PROJECT_NAME}_Server PUBLIC cxx_std_11)