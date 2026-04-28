#ifndef NETWORKNODE_H
#define NETWORKNODE_H
#include <iostream>
#include <string>
#include <list>
#include<cstdlib>
using namespace std ;
class Service ;
class NetworkNode{
    protected:
    int id ;
    string name;
   std::list<Service*> services;
   public:
   //constructo
   NetworkNode(int id ,const string& name,const list<Service*> newService):id(id),name(name),services(newService){}
   NetworkNode():id(0),name(""){}
   NetworkNode( const NetworkNode& obj){
    this->id=obj.id;
    this->name=obj.name;
    this->services=obj.services;
   } 
   //stters 
   void setId(int id );
   void setName(const string& name);
 void setServices(const list<Service*> newService);
 //getters 
 int getId()const;
 string getName()const;
 list<Service*> getServices()const;
   //pure virtual functions 
   virtual  void addService(Service* newService);
   virtual void removeService(Service* newService);
   virtual void scanSystem();
   virtual void checkDataFlow();
   virtual void  testVulnerability();
   virtual void updateSoftware();
   virtual void patchVulnerabilities() ;

   virtual ~NetworkNode(){};

};
#endif
