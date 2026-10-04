#include "../reads/ReadFiles.h"
#include <queue>
#include <algorithm>

/**
 * @file Functions.h
 * @brief Funções para resolver os problemas requisitados.
 */

/**
 * @brief Calcula a melhor forma de distribuir o flow pelo grafo.
 * @param wsn Grafo para ser implementado o Edmonds-Karp.
 * \par Complexity: O((#Service points)*(#Pipes)^2)
 */
void edmondsKarp(WaterSupplyNetwork &wsn);
/**
 * @brief Encontra um caminho que de source a target que dê par aumentar o flow.
 * @param wsn Grafo a ser verificado.
 * @param source Vértice inicial.
 * @param target Vértice final.
 * @return Retorna true se encontrar o "augmenting path" e false caso o contrário.
 * \par Complexity: O(#Service points + #Pipes)
 */
bool findAugmentingPath(WaterSupplyNetwork &wsn, ServicePoint* source, ServicePoint* target);
/**
 * @brief Visita o ponto (vértice) caso ainda não seja visitado e que ainda tenha espaço para aumentar o flow.
 * @param q Fila de vérrtices.
 * @param e Cano para colocar como caminho.
 * @param w Vértice a verificar.
 * @param residual
 * \par Complexity: O(1)
 */
void testAndVisit(queue<ServicePoint*> &q, Pipe *e, ServicePoint *w, double residual);
/**
 * @brief Encontra o residual flow (menor flow possível para aumentar) do caminho entre source e target.
 * @param source Vértice inicial do caminho.
 * @param target Vértice final do caminho.
 * @return Retorna o valor dp residual flow.
 * \par Complexity: O(#Service points)
 */
double findMinResidualAlongPath(ServicePoint *source, ServicePoint *target);
/**
 * @brief Aumenta o flow do caminho entre a source e target.
 * @param source Vértice inicial do caminho.
 * @param target Vértice final do caminho.
 * @param f Quantidade do flow.
 * \par Complexity: O(#Service points)
 */
void augmentFlowAlongPath(ServicePoint *source, ServicePoint *target, unsigned int f);
/**
 * @brief Dá o max flow da cidade.
 * @param cityCode Código da cidade que queremos verificar.
 * @return Retorna o max flow da cidade.
 * \par Complexity: O(#Service points)
 */
int maxFlowCity(const string &cityCode);
/**
 * @brief Dá todas as cidades que estão no water supply network dado como variável.
 * @param wsn Water supply network de onde queremos retirar as cidades.
 * @return Dá return a uma lista com as cidades.
 * /par Complexity: O(#Service points)
 */
vector<City*> getAllCities(WaterSupplyNetwork wsn);
/**
 * @brief Verifica se todas as cidades recebem toda a água que precisam.
 * @param cities Cidades que iremos verificar.
 * @return Dá true se todas as cidades recebem a água que precisam caso contrário dá false.
 * \par Complexity: O(#Cities)
 */
bool checkIfWSNIsEnough(vector<City*> &cities);

/**
 * @brief Cria um novo water supply network com a diferença de pôr certos reservatórios sem água (como se eles não existissem).
 * @param rCode Reservatórios que queremos sem água.
 * @return Novo water supply network com os reservatórios sem água.
 * \par Complexity: O(#Reservoirs)
 */
WaterSupplyNetwork wsnWithoutAReservoir(const string& rCode);
/**
 * @brief Cria um novo water supply network com a diferença de tirar as bombas de água que não queremos.
 * @param psList Lista de bombas de água que queremos tirar.
 * @return Novo water supply network sem as bombas de água que queriamos tirar.
 * \par Complexity: O((#OutPipes * #InPipes) * #PumpingStation)
 */
WaterSupplyNetwork wsnWithoutStation(const vector<string> &psList); //3.2
/**
 * @brief Cria um novo water supply network com a diferença de tirar canos que não queremos.
 * @param pipeList Lista de canos que queremos eliminar.
 * @return Novo water supply network sem os canos que queriamos eliminar.
 * \par Complexity: O(#Pipes)
 */
WaterSupplyNetwork wsnWithoutPipes(const vector<pair<string,string>> &pipeList);//3.3
/**
 * @brief Compara os valores de max flow das cidades antes e depois de alguma alteração no water supply network.
 * @param wsnCopy Novo water supply network com as mudanças.
 * @param affectedCities Retorna as cidades afetadas.
 * @return Dá return true se alguma cidade for afetada (diminuir o max flow) e dá false se nenhuma for afetada.
 * par Complexity: O(#Pipes)
 */
bool checkIfAffected(WaterSupplyNetwork wsnCopy, vector<pair<City*,City*>> &affectedCities);

/**
 * @brief Verifica se a cidade dado pelo input existe.
 * @param cityCode Código da cidade.
 * @return Dá return true se a cidade existir e caso contrário dá false.
 * /par Complexity: O(#Cities^2)
 */
bool cityExists(const string &cityCode);
/**
 * @brief Verifica se o reservatório dado pelo input existe.
 * @param rCode Código do reservatório.
 * @return Dá return true se o reservatório existir e caso contrário dá false.
 * /par Complexity: O(#Reservoirs)
 */
bool reservoirExists(const string &rCode);
/**
 * @brief Verifica se a bomba de água dada pelo input existe.
 * @param psCode Código da bomba de água.
 * @return Dá return true se a bomba de água existir e caso contrário dá false.
 * \par Complexity: O(#Pumping Stations)
 */
bool pumpStationExsists(const string &psCode);
/**
 * @brief Verifica se o cano dado pelo input existe.
 * @param sourceCode Código do local que serve como ínicio do cano.
 * @param targetCode Código do local que serve como final do cano.
 * @return Dá return true se o cano existir e caso contrário dá false.
 * \par Complexity: O(#Pipes)
 */
bool pipeExists(const string &sourceCode, const string &targetCode);