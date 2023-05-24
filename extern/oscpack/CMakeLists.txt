cmake_minimum_required(VERSION 3.25)
project(OSCPack)

# should the library be build as a dynamic or static lib?
option(BUILD_SHARED_LIBS "Build as Static Lib when OFF, and Dynamic/Shared Lib when ON (Default=OFF)" OFF)

if(MINGW OR MSVC)
    set(IpSystemTypePath ${CMAKE_CURRENT_SOURCE_DIR}/oscpack/ip/win32)
    list(APPEND LIBS ws2_32 winmm)
    message(STATUS "Using win32")
else()
    set(IpSystemTypePath ${CMAKE_CURRENT_SOURCE_DIR}/oscpack/ip/posix)
    message(STATUS "Using posix")
endif()

# determine build type
if(BUILD_SHARED_LIBS)
    set(LIB_BUILD_TYPE "SHARED")
    set(LIB_BUILD_TYPE_NAME "dynamic")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
else()
    set(LIB_BUILD_TYPE "STATIC")
    set(LIB_BUILD_TYPE_NAME "static")
endif()
message(STATUS "Build ${LIB_BUILD_TYPE_NAME} Lib ${PROJECT_NAME}")


message(STATUS "${PROJECT_NAME} ${LIB_BUILD_TYPE}")
add_library(${PROJECT_NAME} ${LIB_BUILD_TYPE})

target_include_directories(${PROJECT_NAME} 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/oscpack)

target_sources(${PROJECT_NAME} 
    PRIVATE
    # root
        ${IpSystemTypePath}/NetworkingUtils.cpp
        ${IpSystemTypePath}/UdpSocket.cpp
    # ip
        ${CMAKE_CURRENT_SOURCE_DIR}/oscpack/ip/IpEndpointName.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/oscpack/ip/IpEndpointName.h
        ${CMAKE_CURRENT_SOURCE_DIR}/oscpack/ip/NetworkingUtils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/oscpack/ip/PacketListener.h
        ${CMAKE_CURRENT_SOURCE_DIR}/oscpack/ip/TimerListener.h
        ${CMAKE_CURRENT_SOURCE_DIR}/oscpack/ip/UdpSocket.h
    # osc
        ${CMAKE_CURRENT_SOURCE_DIR}/oscpack/osc/OscTypes.cpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/oscpack/osc/OscReceivedElements.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/oscpack/osc/OscPrintReceivedElements.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/oscpack/osc/OscOutboundPacketStream.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/oscpack/osc/MessageMappingOscPacketListener.h
        ${CMAKE_CURRENT_SOURCE_DIR}/oscpack/osc/OscException.h
        ${CMAKE_CURRENT_SOURCE_DIR}/oscpack/osc/OscHostEndianness.h
        ${CMAKE_CURRENT_SOURCE_DIR}/oscpack/osc/OscOutboundPacketStream.h
        ${CMAKE_CURRENT_SOURCE_DIR}/oscpack/osc/OscPacketListener.h
        ${CMAKE_CURRENT_SOURCE_DIR}/oscpack/osc/OscPrintReceivedElements.h
        ${CMAKE_CURRENT_SOURCE_DIR}/oscpack/osc/OscReceivedElements.h
        ${CMAKE_CURRENT_SOURCE_DIR}/oscpack/osc/OscTypes.h)

if(LIB_BUILD_TYPE_NAME STREQUAL "SHARED")
    set_target_properties(${PROJECT_NAME} PROPERTIES
            IMPORTED_LOCATION "${DEPENDENCIES_DIR}/${PROJECT_NAME}/bin/${PROJECT_NAME}.dll"
            IMPORTED_IMPLIB "${DEPENDENCIES_DIR}/${PROJECT_NAME}/lib/${PROJECT_NAME}.lib"
            INTERFACE_INCLUDE_DIRECTORIES "${DEPENDENCIES_DIR}/${PROJECT_NAME}/include"
            )
endif()

# if there are libs, link against them
list(LENGTH LIBS LIBLEN)
if(NOT ${LIBLEN} EQUAL 0)
    # add the required libraries on windows
    target_link_libraries(${PROJECT_NAME}
            PUBLIC
                ${LIBS})
    message(STATUS "Build with libraries " ${LIBS})

endif()