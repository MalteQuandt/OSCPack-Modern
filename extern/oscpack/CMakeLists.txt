cmake_minimum_required(VERSION 3.25)
project(OSCPack)

if(WIN32)
    set(IpSystemTypePath ${CMAKE_CURRENT_SOURCE_DIR}/oscpack/ip/win32)
    set(LIBS ${LIBS} Ws2_32 winmm)
    message(STATUS "Using win32")
else()
    set(IpSystemTypePath ${CMAKE_CURRENT_SOURCE_DIR}/oscpack/ip/posix)
    message(STATUS "Using posix")
endif()

add_library(${PROJECT_NAME} STATIC)

target_include_directories(${PROJECT_NAME} 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/oscpack)

target_sources(${PROJECT_NAME} 
    PRIVATE 
    # ip folder sources
        ${CMAKE_CURRENT_SOURCE_DIR}/oscpack/ip/IpEndpointName.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/oscpack/ip/IpEndpointName.h
        ${CMAKE_CURRENT_SOURCE_DIR}/oscpack/ip/NetworkingUtils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/oscpack/ip/PacketListener.h
        ${CMAKE_CURRENT_SOURCE_DIR}/oscpack/ip/TimerListener.h
        ${CMAKE_CURRENT_SOURCE_DIR}/oscpack/ip/UdpSocket.h
    # 
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
        ${CMAKE_CURRENT_SOURCE_DIR}/oscpack/osc/OscTypes.h
        ${IpSystemTypePath}/NetworkingUtils.cpp
        ${IpSystemTypePath}/UdpSocket.cpp
        
        )
if(MINGW)
    target_link_libraries(${PROJECT_NAME} PUBLIC ws2_32 winmm)
endif()