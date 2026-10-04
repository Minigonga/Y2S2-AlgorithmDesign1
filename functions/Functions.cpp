#include "Functions.h"

/**
 * @file Functions.cpp
 * @brief Funções para resolver os problemas requisitados.
 */
void edmondsKarp(WaterSupplyNetwork &wsn) {
    wsn.createSuperSource();
    wsn.createSuperSink();
    ServicePoint * s = wsn.findServicePoint("RSource");
    ServicePoint * t = wsn.findServicePoint("CSink");

    for (auto sp: wsn.getServicePoints()) {
        for (auto p: sp->getOutPipes()) {
            p->setFlow(0);
        }
    }
    while (findAugmentingPath(wsn, s, t)) {
        unsigned int f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
    }
    for (auto sp: wsn.getServicePoints()) {
        if (sp->getCode()[0]=='C') {
            City* c = static_cast<City *>(sp);
            for (auto p: c->getInPipes()) {
                c->addMaxFlow(p->getFlow());
            }
        }
    }
}

bool findAugmentingPath(WaterSupplyNetwork &wsn, ServicePoint* source, ServicePoint* target) {
    for (auto sp : wsn.getServicePoints()) {
        sp->setVisited(false);
    }
    source->setVisited(true);
    queue<ServicePoint*> q;
    q.push(source);
    while (!q.empty() && ! target->isVisited()) {
        auto sp = q.front();
        q.pop();
        for (auto p: sp->getOutPipes()) {
            testAndVisit(q, p, p->getDest(), p->getCapacity() - p->getFlow());
        }
        for (auto p: sp->getInPipes()) {
            testAndVisit(q, p, p->getSource(), p->getFlow());
        }
    }
    return target->isVisited();
}
void testAndVisit(queue<ServicePoint*> &q, Pipe *e, ServicePoint *w, double residual) {
    if (!w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}
double findMinResidualAlongPath(ServicePoint *source, ServicePoint *target) {
    unsigned int f = INT_MAX;
    for (auto sp = target; sp != source; ) {
        auto p = sp->getPath();
        if (p->getDest() == sp) {
            f = min(f, p->getCapacity() - p->getFlow());
            sp = p->getSource();
        } else {
            f = std::min(f, p->getFlow());
            sp = p->getDest();
        }
    }
    return f;
}
void augmentFlowAlongPath(ServicePoint *source, ServicePoint *target, unsigned int f) {
    for (auto sp = target; sp != source;) {
        auto p = sp->getPath();
        double flow = p->getFlow();
        if (p->getDest() == sp) {
            p->setFlow(flow + f);
            sp = p->getSource();
        } else {
            p->setFlow(flow - f);
            sp = p->getDest();
        }
    }
}

int maxFlowCity(const string &cityCode) { //2.1
    auto sp = waterSupplyNetwork.findServicePoint(cityCode);
    City* c = static_cast<City *>(sp);
    return c->getMaxFlow();
}
vector<City*> getAllCities(WaterSupplyNetwork wsn) { //2.1
    vector<City*> cities;
    for (auto sp: wsn.getServicePoints()) {
        if (sp->getCode()[0]=='C' && sp->getCode()!="CSink") {
            City* c = static_cast<City *>(sp);
            cities.push_back(c);
        }
    }
    return cities;
}

bool checkIfWSNIsEnough(vector<City*> &cities) { //2.2
    bool flag = true;
    for (auto sp: waterSupplyNetwork.getServicePoints()) {
        if (sp->getCode()[0]=='C' && sp->getCode()!="CSink") {
            City* c = static_cast<City *>(sp);
            if (c->getDemand()>c->getMaxFlow()) {
                flag = false;
                cities.push_back(c);
            }
        }
    }
    return flag;
}

WaterSupplyNetwork wsnWithoutAReservoir(const string& rCode) { //3.1
    WaterSupplyNetwork wsnCopy;
    readFiles(wsnCopy);
    ServicePoint *sp = wsnCopy.findServicePoint(rCode);
    Reservoir* r = static_cast<Reservoir *>(sp);
    r->setMaxDelivery(0);
    edmondsKarp(wsnCopy);
    return wsnCopy;
}
WaterSupplyNetwork wsnWithoutStation(const vector<string> &psList) { //3.2
    WaterSupplyNetwork wsnCopy;
    readFiles(wsnCopy);
    for (string ps: psList) {
        ServicePoint *sp = wsnCopy.findServicePoint(ps);
        vector<Pipe*> change= sp->getInPipes();
        for (Pipe* pipe: change){
            wsnCopy.deletePipe(pipe->getSource()->getCode(),pipe->getDest()->getCode());
        }
        change= sp->getOutPipes();
        for (Pipe* pipe: change){
            wsnCopy.deletePipe(pipe->getSource()->getCode(),pipe->getDest()->getCode());
        }
    }
    edmondsKarp(wsnCopy);
    return wsnCopy;
}
WaterSupplyNetwork wsnWithoutPipes(const vector<pair<string,string>> &pipeList) { //3.2
    WaterSupplyNetwork wsnCopy;
    readFiles(wsnCopy);
    for (pair<string,string> pipe: pipeList) {
        wsnCopy.deletePipe(pipe.first,pipe.second);
        wsnCopy.deletePipe(pipe.second,pipe.first);
    }
    edmondsKarp(wsnCopy);
    return wsnCopy;
}

bool checkIfAffected(WaterSupplyNetwork wsnCopy, vector<pair<City*,City*>> &affectedCities) {
    bool isAffected = false;
    for (auto c: getAllCities(waterSupplyNetwork)) {
        for(auto cCopy: getAllCities(wsnCopy)) {
            if (c->getCode() == cCopy->getCode() && c->getMaxFlow() != cCopy->getMaxFlow()) {
                affectedCities.push_back({c,cCopy});
                isAffected = true;
            }
        }
    }
    return isAffected;
}

bool cityExists(const string &cityCode) {
    return cityCode[0] == 'C' && waterSupplyNetwork.findServicePoint(cityCode) != nullptr;
}
bool reservoirExists(const string &rCode) {
    return rCode[0] == 'R' && waterSupplyNetwork.findServicePoint(rCode) != nullptr;
}
bool pumpStationExsists(const string &psCode) {
    return psCode[0] == 'P' && waterSupplyNetwork.findServicePoint(psCode) != nullptr;
}
bool pipeExists(const string &sourceCode, const string &targetCode) {
    auto pipe = waterSupplyNetwork.findPipe(sourceCode, targetCode);
    auto reverse = waterSupplyNetwork.findPipe(targetCode, sourceCode);
    return pipe != nullptr || (reverse != nullptr && reverse->getReverse());
}