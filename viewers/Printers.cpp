#include "Printers.h"

/**
 * @file Printers.cpp
 * @brief Dá print a todos os resultados obtidos pelas funções presentes no ficheiro Functions.cpp.
 */

void printMaxFlowCity(const string & cityCode) {
    cout<<"The max flow of the city "<<cityCode<<" is: "<<maxFlowCity(cityCode)<<endl;
}
void printMaxFlowCities() {
    vector<City*> cities = getAllCities(waterSupplyNetwork);
    for (auto c: cities) {
        cout<<"City: "<<c->getCode()<<"\t\tMaxFlow: "<<c->getMaxFlow()<<endl;
    }
}

void printCheckIfWSNIsEnough() {
    vector<City *> cities;
    unsigned int demand = 0, flow = 0;
    bool isEnough = checkIfWSNIsEnough(cities);
    if (isEnough) {
        cout<<"The water from the reservoirs was enough to supply all the cities!"<<endl;
    } else {
        cout<<"The water from the reservoirs was not enough to supply all the cities."<<endl;
        for (auto c: cities) {
            cout<<"City: "<<c->getCode()<<"\t\tDemand: "<<c->getDemand()<<"\t\tActual flow: "<<c->getMaxFlow()<<"\t\tMissing amount: "<<c->getDemand()-c->getMaxFlow()<<endl;
        }
    }
}

void printWSNWithoutAReservoir(const string &rCode) {
    vector<pair<City*,City*>> affectedCities;
    bool isAffected= checkIfAffected(wsnWithoutAReservoir(rCode), affectedCities);
    if (isAffected) {
        cout<<"The removal of the reservoir "<<rCode<<" affected the cities:"<<endl;
        for (auto p: affectedCities) {
            cout<<"City: "<<p.first->getCode()<<"\t\tOld Flow: "<<p.first->getMaxFlow()<<"\t\tNew Flow: "<<p.second->getMaxFlow()<<endl;
        }
    } else {
        cout<<"The removal of the reservoir "<<rCode<<" didn't affect the cities."<<endl;
    }
}
void printWSNWithoutStation(const vector<string> &psList) {
    vector<pair<City*,City*>> affectedCities;
    bool isAffected= checkIfAffected(wsnWithoutStation(psList), affectedCities);
    if (isAffected) {
        cout<<"The removal of ";
        for (auto ps: psList) cout<<ps<<" ";
        cout<<"affected the cities:"<<endl;
        for (auto p: affectedCities) {
            cout<<"City: "<<p.first->getCode()<<"\t\tOld Flow: "<<p.first->getMaxFlow()<<"\t\tNew Flow: "<<p.second->getMaxFlow()<<endl;
        }
    } else {
        cout<<"The removal of this/these pumping station/s didn't affect the cities."<<endl;
    }
}
void printWSNWithoutPipes(const vector<pair<string,string>> &pipeList) {
    vector<pair<City*,City*>> affectedCities;
    bool isAffected= checkIfAffected(wsnWithoutPipes(pipeList), affectedCities);
    if (isAffected) {
        cout<<"The removal of ";
        for (auto pipe: pipeList) cout<<pipe.first<<"-->"<<pipe.second<<" ";
        cout<<"affected the cities:"<<endl;
        for (auto p: affectedCities) {
            cout<<"City: "<<p.first->getCode()<<"\t\tOld Flow: "<<p.first->getMaxFlow()<<"\t\tNew Flow: "<<p.second->getMaxFlow()<<endl;
        }
    } else {
        cout<<"The removal of this/these pipe/s didn't affect the cities."<<endl;
    }
}