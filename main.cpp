#include "viewers/Menus.h"

/**
 * @file main.cpp
 * @brief Inicia o programa.
 */

WaterSupplyNetwork waterSupplyNetwork;

int main() {
    readFiles(waterSupplyNetwork);
    edmondsKarp(waterSupplyNetwork);
    mainMenu();
    return 0;
}