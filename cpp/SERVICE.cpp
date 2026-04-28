#include "../headers/SERVICE.h"
//setters
void Service::setPort(int port){
    this->port=port;
}   
void Service::setType(const string& type){
    this->type=type;
}
void Service::setName(const string& name){
    this->name=name;
}
//getters
int Service::getPort()const{    
    return this->port;
}
string Service::getType()const{
    return this->type;
}
string Service::getName()const{
    return this->name;
}
//methods
bool Service::isActive(){
    return this->isRunning;
}





