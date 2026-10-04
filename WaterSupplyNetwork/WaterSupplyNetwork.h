#ifndef DA2024_PRJ1_G4_WATERSUPPLYNETWORK_H
#define DA2024_PRJ1_G4_WATERSUPPLYNETWORK_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

/**
 * @file WaterSupplyNetwork.h
 * @brief Cria a estrutura de dados da water supply network.
 */

class Pipe;
class ServicePoint;


/**
 * @brief Classe usada para gerir o sistema de água (grafo).
 */
class WaterSupplyNetwork {
    vector<ServicePoint*> servicePoints;
    vector<Pipe*> pipes;
public:
    ServicePoint* findServicePoint(string const &code);
    Pipe* findPipe(string const &sourceCode, string const &targetCode);

    void addServicePoint(ServicePoint* sp);
    void addPipe(const string &sourceCode, const string &destCode, const unsigned int &capacity, const bool &unidirectional);

    int getNumServicePoints() const;
    vector<ServicePoint*> getServicePoints() const;
    vector<Pipe*> getPipes() const;

    vector<ServicePoint*> dfs() const;
    vector<ServicePoint*> dfs(const string &source) const;
    void dfsVisit() const;
    vector<ServicePoint*> bfs(const string &source) const;

    bool isDAG() const;
    bool dfsIsDAG(ServicePoint* sp) const;
    vector<string> topsort() const;

    void deletePipe(string const &sourceCode, string const &targetCode);
    void createSuperSource();
    void createSuperSink();
};

/**
 * @brief Classe que cria os pontos de serviço e é abstrata para as cidades e para os reservatórios (vértices).
 */

class ServicePoint {
    string id, code;
    bool visited = false, processing = false; //processing é para isDAG
    vector<Pipe*> outPipes, inPipes;  //Edges que saem e que entram
    Pipe* path = nullptr;
    unsigned int indegree = 0; // para o topsort
    double dist = 0;
public: //sets, gets, isVisited
    ServicePoint(const string &id, const string &code);

    string getId() const;
    string getCode() const;
    bool isVisited() const;
    bool isProcessing() const;
    vector<Pipe*> getOutPipes() const;
    vector<Pipe*> getInPipes() const;
    Pipe* getPath() const;
    unsigned int getIndegree() const;
    double getDist() const;

    //meter os sets que vamos utilizar
    void setVisited(const bool &visited);
    void setProcessing(const bool &processing);
    void addOutPipe(Pipe* p);
    void addInPipe(Pipe* p);
    void setPath(Pipe* path);
    void setIndegree(const double &indegree);
    void setDist(const double &dist);
    void removeOutPipe(const string &target);
    void removeInPipe(const string &source);
};

/**
 * @brief Classe que cria as cidades (vértices finais).
 */
class City : public ServicePoint {
    string name;
    unsigned int demand, population, maxFlow = 0;

public:
    City(const string &id, const string &code, const string &name, const unsigned int &demand, const unsigned int &population);

    string getName() const;
    unsigned int getDemand() const;
    unsigned int getPopulation() const;
    unsigned int getMaxFlow() const;
    void addMaxFlow(const unsigned int &flow);
};

/**
 * @brief Classe que cria os reservátorios (vértices iniciais).
 */
class Reservoir : public ServicePoint {
protected:
    string name, municipality;
    unsigned int maxDelivery;
public:
    Reservoir(const string &id, const string &code, const string &name, const string &municipality, const unsigned int &maxDelivery);

    string getName() const;
    string getMunicipality() const;
    unsigned int getMaxDelivery() const;

    void setMaxDelivery(const unsigned int &maxDelivery);
};

/**
 * @brief Classe que cria as estações (vértices do meio).
 */
class Station : public ServicePoint {

public:
    Station(const string id, const string &code);
};

/**
 * @brief Classe que cria os canos onde circula a água (arestas).
 */
class Pipe {
    ServicePoint* source = nullptr;
    ServicePoint* destination = nullptr;
    unsigned int capacity, flow;   //weight & flow
    bool reverse = false;      //bidirectional aux
public:
    Pipe(ServicePoint* source, ServicePoint* destination, const unsigned int &capacity);

    ServicePoint* getSource() const;
    ServicePoint* getDest() const;
    unsigned int getCapacity() const;
    unsigned int getFlow() const;
    bool getReverse() const; // unidirectional if false

    void setReverse(const bool &isReverse);
    void setFlow(const unsigned int &flow);
    void setReverse(Pipe* reverse);
};


#endif //DA2024_PRJ1_G4_WATERSUPPLYNETWORK_H