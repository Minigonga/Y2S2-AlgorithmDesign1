cmake_minimum_required(VERSION 3.27)
project(DA2024_PRJ1_G4)

set(CMAKE_CXX_STANDARD 14)

include_directories(WaterSupplyNetwork)

add_executable(DA2024_PRJ1_G4
        WaterSupplyNetwork/WaterSupplyNetwork.cpp
        WaterSupplyNetwork/WaterSupplyNetwork.h
        Reads/ReadFiles.h
        Reads/ReadFiles.cpp
        main.cpp
        functions/Functions.cpp
        viewers/Printers.cpp
        viewers/Menus.cpp
)
