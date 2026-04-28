#ifndef SERVICE_H
#define SERVICE_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
using namespace std;
class Service{
    protected:
    int port;
    string type;
    string name;
    bool isRunning;
     
    public:
    Service(int port,const string& type,const string& name):port(port),type(type),name(name),isRunning(false){}
    Service():port(0),type(""),name(""),isRunning(false){}
    Service(const Service& obj):port(obj.port),type(obj.type),name(obj.name),isRunning(obj.isRunning){}
    //setters
    void setPort(int port);
    void setType(const string& type);
    void setName(const string& name);
    //getters
    int getPort()const;
    string getType()const;
    string getName()const;
    
    //methods
    bool isActive();
   virtual void scan()=0;
virtual void execute()=0;
virtual void stop()=0;
virtual ~Service(){};

};
#endif
