#include "ReadFiles.h"

/**
 * @file ReadFiles.cpp
 * @brief Funções para ler e guardar os ficheiros .csv
 */

void readCities(WaterSupplyNetwork &wsn) {
    ifstream in("../dataset/Cities.csv");
    string line, city, id, code, strDemand, strPopulation;
    unsigned int demand, population;
    getline(in, line);
    while(getline(in, city, ','), getline(in, id, ','), getline(in, code, ','), getline(in, strDemand, ','), getline(in, strPopulation)) {
        demand = stoi(strDemand);
        population = stod(strPopulation);
        wsn.addServicePoint(new City(id, code, city, demand, population));
    }
    in.close();
}
void readReservoirs(WaterSupplyNetwork &wsn) {
    ifstream in("../dataset/Reservoirs.csv");
    string line, name, id, code, municipality, strMaxDelivery;
    unsigned int maxDelivery;
    getline(in, line);
    while(getline(in, name, ','), getline(in, municipality, ','), getline(in, id, ','), getline(in, code, ','), getline(in, strMaxDelivery)) {
        maxDelivery = stoi(strMaxDelivery);
        wsn.addServicePoint(new Reservoir(id, code, name, municipality, maxDelivery));
    }
    in.close();
}
void readStations(WaterSupplyNetwork &wsn) {
    ifstream in("../dataset/Stations.csv");
    string line, id, code;
    getline(in, line);
    while(getline(in, id, ','), getline(in, code)) {
        wsn.addServicePoint(new Station(id, code));
    }
    in.close();
}
void readServicePoints(WaterSupplyNetwork &wsn){
    readCities(wsn);
    readReservoirs(wsn);
    readStations(wsn);
}

void readPipes(WaterSupplyNetwork &wsn) {
    ifstream in("../dataset/Pipes.csv");
    string line, source, dest, strCapacity, strUnidirectional;
    unsigned int capacity;
    bool unidirectional;
    getline(in, line);
    while(getline(in, source, ','), getline(in, dest, ','), getline(in, strCapacity, ','), getline(in, strUnidirectional)) {
        capacity = stoi(strCapacity);
        istringstream iss(strUnidirectional);
        iss >> unidirectional;
        wsn.addPipe(source, dest, capacity, unidirectional);
    }
    in.close();
}

void readFiles(WaterSupplyNetwork &wsn) {
    readServicePoints(wsn);
    readPipes(wsn);
}