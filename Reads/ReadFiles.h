#ifndef DA2024_PRJ1_G4_READFILES_H
#define DA2024_PRJ1_G4_READFILES_H

#include "../GlobalVariables.h"
#include <fstream>
#include <sstream>

/**
 * @file ReadFiles.h
 * @brief Funções para ler e guardar os ficheiros .csv
 */

/**
 * @brief Lê o ficheiro "Cities.csv" e guarda no wsn.
 * @param wsn
 */
void readCities(WaterSupplyNetwork &wsn);

/**
 * @brief Lê o ficheiro "Reservoirs.csv" e guarda no wsn.
 * @param wsn
 */
void readReservoirs(WaterSupplyNetwork &wsn);
/**
 * @brief Lê o ficheiro "Stations.csv" e guarda no wsn.
 * @param wsn
 */
void readStations(WaterSupplyNetwork &wsn);

/**
 * @brief Lê os ficheiros "Cities.csv", "Reservoirs.csv" e "Stations.csv" e guarda no wsn.
 * @param wsn
 */
void readServicePoints(WaterSupplyNetwork &wsn);
/**
 * @brief Lê o ficheiro "Pipes.csv" e guarda no wsn.
 * @param wsn
 */
void readPipes(WaterSupplyNetwork &wsn);
/**
 * @brief Lê todos os ficheiros e guarda no wsn.
 * @param wsn
 */
void readFiles(WaterSupplyNetwork &wsn);

#endif //DA2024_PRJ1_G4_READFILES_H
