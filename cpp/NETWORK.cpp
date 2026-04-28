#include "../headers/NETWORK.h"
#include "../headers/SERVICE.h"
void NetworkNode::setId(int id){
    this->id=id;
}
void NetworkNode::setName(const string& name){
    this->name=name;
}
void NetworkNode::setServices(const list<Service*> newService){
    this->services=newService;
}
//getters 
int NetworkNode::getId()const{
    return this->id;
}
string NetworkNode::getName()const{
    return this->name;
}
list<Service*> NetworkNode::getServices()const{
    return this->services;
}
//methods 

void NetworkNode::addService(Service* newService){
        if(newService==nullptr){
            cout<<"!  WARNING \n";
            return ;
        }
        
        //advanced for loop to check if the service already exists in the workstation
            for(auto it =getServices().begin();it != getServices().end();++it){
                if( (*it)->getName()==newService->getName())
                {
                    cout<<"Service already exists \n";
                    return ;
                }
            }
            services.push_back(newService);
            cout<<"Service added successfully \n";
}
void NetworkNode::removeService(Service* newService){
        if(newService==nullptr)
        {
        cout<<"! WANINRG  CANNOT REMOVE NULL SERVICE\n";
            return ;
        }
        //advanced for loop to check if the service exists in the workstation
        for(auto it =getServices().begin();it != getServices().end(); ++it){
            if((*it)->getName()==newService->getName())
            {  
                cout<<"Removing service....\n";
                cout<<"Stopping service....\n";
                (*it)->stop();;
                 cout<<"Service stopped successfully \n";
                    cout<<"Removing service from workstation....\n";
                services.erase(it);//erase keyword to remove the service from the list and it will automatically shift the remaining services to fill the gap
                    cout<<"Service removed succefully\n";
                return;
            }
             
            

        }
        cout<<"Service not found \n";
}
//these methods will be overriden in child classes 


void NetworkNode::scanSystem() {}

void NetworkNode::checkDataFlow() {}

void NetworkNode::testVulnerability() {}

void NetworkNode::updateSoftware() {}
void NetworkNode::patchVulnerabilities() {}

