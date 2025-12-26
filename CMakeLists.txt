cmake_minimum_required(VERSION 3.16)
project(NovaClient LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Engine einbinden
find_package(NovaForge REQUIRED)

add_library(novaclient
    src/Client.cpp
    src/ClientState.cpp
    src/Net/PacketBuffer.cpp
    src/Net/PacketRegistry.cpp
    src/Net/Packets_Test.cpp
)

target_include_directories(novaclient PUBLIC include)
target_link_libraries(novaclient PRIVATE NovaForge::NovaForge)

add_executable(novaclient_demo src/main.cpp)
target_link_libraries(novaclient_demo PRIVATE novaclient)

if (WIN32)
    target_link_libraries(novaclient PRIVATE ws2_32)
endif()
