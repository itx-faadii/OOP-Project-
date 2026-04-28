#ifndef CREDENTIALSTORE_H
#define CREDENTIALSTORE_H
#include<iostream>
#include<fstream>//library for file handlingfast 
#include<string>
#include <cstdlib>
# include "ActivityLogger.h"
#include <cstdio>
#include <list>
using namespace std;
class CredentialStore{
    private:
    string username;
    string password;
    list<string> wordlist;
    int attempts;
    public:
    //consturctores
    CredentialStore(const string& username,const string& password):username(username),password(password),attempts(0){}
    CredentialStore():username(""),password(""),attempts(0){}
    CredentialStore(const CredentialStore& obj):username(obj.username),password(obj.password),wordlist(obj.wordlist),attempts(obj.attempts){}
    //setters
    void setUsername(const string& username);
    void setPassword(const string& password);
    void setWordlist(const list<string>& wordlist);
    void setAttempts(int attempts);
    //getters
    string getUsername()const;

    string getPassword()const;
    list<string> getWordlist()const;
    int getAttempts()const;
    //methods
    void loadDefultWordlist();
    bool checkPassword(const string& attempt);
    void bruteForceAttack(const  Logger& logger);
    bool isWeak();
    void display();
    ~CredentialStore(){};
};
#endif 
