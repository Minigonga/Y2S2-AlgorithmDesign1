#include "WaterSupplyNetwork.h"

/**
 * @file WaterSupplyNetwork.cpp
 * @brief Cria a estrutura de dados da water supply network.
 */

//WATERSUPPLYNETWORK
ServicePoint* WaterSupplyNetwork::findServicePoint(string const &code) {
    for (ServicePoint* sp: servicePoints) {
        if (sp->getCode() == code) {
            return sp;
        }
    }
    return nullptr;
}
Pipe* WaterSupplyNetwork::findPipe(string const &sourceCode, string const &destCode) {
    for (Pipe* p: pipes) {
        if (p->getSource()->getCode() == sourceCode && p->getDest()->getCode() == destCode) {
            return p;
        }
    }
    return nullptr;
}
void WaterSupplyNetwork::addServicePoint(ServicePoint* sp) {servicePoints.push_back(sp);}
void WaterSupplyNetwork::addPipe(const string &sourceCode, const string &destCode, const unsigned int &capacity, const bool &unidirectional) {
    if (sourceCode == destCode) return;
    ServicePoint* source = findServicePoint(sourceCode);
    ServicePoint* dest = findServicePoint(destCode);
    Pipe* p = new Pipe(source, dest, capacity);
    source->addOutPipe(p);
    dest->addInPipe(p);
    if (!unidirectional) p->setReverse(true);
    pipes.push_back(p);
}
int WaterSupplyNetwork::getNumServicePoints() const {return servicePoints.size();}
vector<ServicePoint*> WaterSupplyNetwork::getServicePoints() const {return servicePoints;}
vector<Pipe*> WaterSupplyNetwork::getPipes() const {return pipes;}
void WaterSupplyNetwork::deletePipe(string const &sourceCode, string const &targetCode){
    Pipe* pipe = findPipe(sourceCode,targetCode);
    if (pipe == nullptr) return;
    pipe->setReverse(false);
    ServicePoint *source = findServicePoint(sourceCode);
    ServicePoint *target = findServicePoint(targetCode);
    source->removeOutPipe(targetCode);
    target->removeInPipe(sourceCode);
    vector<Pipe*> newPipes;
    for (auto p: pipes) {
        if (p->getSource()->getCode() != sourceCode || p->getDest()->getCode() != targetCode) {
            newPipes.push_back(p);
        }
    }
    pipes = newPipes;
}
void WaterSupplyNetwork::createSuperSource(){
    ServicePoint* sSource = new ServicePoint("1000", "RSource");
    addServicePoint(sSource);
    for (ServicePoint* sp: servicePoints) {
        if(sp->getCode()[0] == 'R') {
            Reservoir* r = static_cast<Reservoir *>(sp);
            addPipe("RSource", r->getCode(), r->getMaxDelivery(), 1);
        }
    }
}
void WaterSupplyNetwork::createSuperSink() {
    ServicePoint* sSink = new ServicePoint("1001", "CSink");
    addServicePoint(sSink);
    for (ServicePoint* sp: servicePoints) {
        if(sp->getCode()[0] == 'C') {
            City* c = static_cast<City *>(sp);
            addPipe(c->getCode(), "CSink", c->getDemand(), 1);
        }
    }
}



//SERVICEPOINT
ServicePoint::ServicePoint(const string &id, const string &code) : id(id), code(code) {}
string ServicePoint::getId() const {return id;}
string ServicePoint::getCode() const {return code;}
bool ServicePoint::isVisited() const {return visited;}
bool ServicePoint::isProcessing() const {return processing;}
vector<Pipe*> ServicePoint::getOutPipes() const {return outPipes;}
vector<Pipe*> ServicePoint::getInPipes() const {return inPipes;}
Pipe* ServicePoint::getPath() const {return path;}
unsigned int ServicePoint::getIndegree() const {return indegree;}
double ServicePoint::getDist() const {return dist;}


void ServicePoint::setVisited(const bool &visited) {this->visited = visited;}
void ServicePoint::setProcessing(const bool &processing) {this->processing = processing;}
void ServicePoint::addOutPipe(Pipe* p) {outPipes.push_back(p);}
void ServicePoint::addInPipe(Pipe* p) {inPipes.push_back(p);}
void ServicePoint::setPath(Pipe* path) {this->path = path;}
void ServicePoint::setIndegree(const double &indegree) {this->indegree = indegree;}
void ServicePoint::setDist(const double &dist) {this->dist = dist;}
void ServicePoint::removeOutPipe(const string &target){
    vector<Pipe*> change;
    for(Pipe* pipe: outPipes){
        if (pipe->getDest()->getCode()!=target){
            change.push_back(pipe);
        }
    }
    outPipes=change;
}
void ServicePoint::removeInPipe(const string &source){
    vector<Pipe*> change;
    for(Pipe* pipe: inPipes){
        if (pipe->getSource()->getCode()!=source){
            change.push_back(pipe);
        }
    }
    inPipes=change;
}


//CITY
City::City(const string &id, const string &code, const string &name, const unsigned int &demand, const unsigned int &population) : ServicePoint(id, code) {
    this->name = name;
    this->demand = demand;
    this->population = population;
}
string City::getName() const {return name;}
unsigned int City::getDemand() const {return demand;}
unsigned int City::getPopulation() const {return population;}
unsigned int City::getMaxFlow() const {return maxFlow;}
void City::addMaxFlow(const unsigned int &flow) {maxFlow += flow;}

//RESERVOIR
Reservoir::Reservoir(const std::string &id, const std::string &code, const std::string &name, const std::string &municipality, const unsigned int &maxDelivery) : ServicePoint(id, code) {
    this->name = name;
    this->municipality = municipality;
    this->maxDelivery = maxDelivery;
}
string Reservoir::getName() const {return name;}
string Reservoir::getMunicipality() const {return municipality;}
unsigned int Reservoir::getMaxDelivery() const {return maxDelivery;}

void Reservoir::setMaxDelivery(const unsigned int &maxDelivery) {this->maxDelivery = maxDelivery;}



//STATION
Station::Station(const std::string id, const std::string &code) : ServicePoint(id, code) {}



//PIPE
Pipe::Pipe(ServicePoint* source, ServicePoint* destination, const unsigned int &capacity) {
    this->source = source;
    this->destination = destination;
    this->capacity = capacity;
}
ServicePoint* Pipe::getSource() const {return source;}
ServicePoint* Pipe::getDest() const {return destination;}
unsigned int Pipe::getCapacity() const {return capacity;}
unsigned int Pipe::getFlow() const {return flow;}
bool Pipe::getReverse() const {return reverse;}

void Pipe::setReverse(const bool &isReverse) {this->reverse = isReverse;}
void Pipe::setFlow(const unsigned int &flow) {this->flow = flow;}
void Pipe::setReverse(Pipe* reverse) {this->reverse = reverse;}

