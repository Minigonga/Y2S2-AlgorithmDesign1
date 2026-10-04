#include "../functions/Functions.h"
/**
 * @file Printers.h
 * @brief Dá print a todos os resultados obtidos pelas funções presentes no ficheiro Functions.cpp.
 */


/**
 * @brief Dá print ao max flow de uma cidade [T2.1].
 * @param cityCode Código da cidade que se quer verificar o maxflow.
 */
void printMaxFlowCity(const string &cityCode);
/**
 * @brief Dá print ao max flow de todas as cidades [T2.1].
 */
void printMaxFlowCities();
/**
 * @brief Dá print às cidades que estão com falta de água e os valores em falta, se nenhuma precisar de água diz que estão todas abastecidas [T2.2].
 */
void printCheckIfWSNIsEnough();

/**
 * @brief Dá print às cidades que sofrem com a falta do reservatório dado como input.
 * @param rCode Código do reservatório.
 */
void printWSNWithoutAReservoir(const string &rCode);

/**
 * @brief Dá print às cidades que sofrem com a falta das bombas de água dadas como input.
 * @param psList Lista de código das bombas de água.
 */
void printWSNWithoutStation(const vector<string> &psList);

/**
 * @brief Dá print às cidades que sofrem com a falta dos canos dados como input.
 * @param pipeList Lista de canos.
 */
void printWSNWithoutPipes(const vector<pair<string,string>> &pipeList);