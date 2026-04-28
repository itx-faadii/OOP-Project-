#ifndef SSHSERVICE_H
#define SSHSERVICE_H
#include "SERVICE.h"
#include <string>
#include <iostream>
#include <unistd.h> // for sleep function in linux
#include <cstdlib>
#include <cstdio>
using namespace std;
class SSHService:public Service{
int authAttempts;// authenutication attempts
int maxTries;//koi kitni max tries kr skta ha brute force attack krne ke liye
public:
//perametrized constructr 
 SSHService(int port,const string& type,const string& name,int auth,int max):
 Service(port,type,name),authAttempts(auth),maxTries(max){}
//default constr 
SSHService():Service(),authAttempts(0),maxTries(5) {}
//copy constr 
SSHService(const SSHService& obj):Service(obj),authAttempts(obj.authAttempts),maxTries(obj.maxTries ){}
//setters 
void setAuthAttempts(int x);
void setMaxTries(int x);
//getters
int getAuthAttempts()const;
int getMaxTries()const;
//methods of parent service  overrriden 
//stop function override kia aur agur poert open thu to usy real ma stop kr dy ga 
void stop() override {
    cout << "\n[TERMINATING] Stopping SSH Service..." << endl;
  if(!isRunning){
        cout<<"[!] SSH Service is not running.\n";
        return ;
    }
    #ifdef _WIN32
        // Windows command to stop the service
        if (system("net stop sshd") == 0) {
            isRunning = false;
            cout << "[-] SUCCESS: Windows SSH Service stopped." << endl;
        } else {
            cout << "[!] ERROR: Failed to stop Windows SSH Service." << endl;
        }
    #else
        // Linux command to stop the service
        if (system("sudo systemctl stop ssh") == 0) {
            isRunning = false;
            cout << "[-] SUCCESS: Linux SSH Daemon stopped." << endl;
        } else {
            cout << "[!] ERROR: Failed to stop Linux SSH Service." << endl;
        }
    #endif
}
//sevrice class ka method oveeride kia ha idhr commands are searcedh from google

void execute() override {
    cout << "\n[INIT] Starting Real-Time SSH Service Activation..." << endl;

    #ifdef _WIN32
        // --- WINDOWS LOGIC (Powerful PowerShell Command) searched from google  ---
        cout << "[*] Checking for OpenSSH Server on Windows..." << endl;
        
        //  Check if service exists
        int check = system("sc query sshd >nul 2>&1");

        if (check != 0) {
            cout << "[!] SSH not found. Launching Powerful Installer..." << endl;
            // Wahi powerful command searcehd from google
            string installCmd = "powershell -Command \"Start-Process powershell -Verb RunAs -ArgumentList 'Add-WindowsCapability -Online -Name OpenSSH.Server~~~~0.0.1.0'\"";
            
            system(installCmd.c_str());
            cout << "[?] Please wait for the blue PowerShell window to finish..." << endl;
            // waiting 
        }

        // Start the service will be start 
        cout << "[*] Attempting to start SSH service (sshd)..." << endl;
        if (system("net start sshd") == 0) {
            isRunning = true;
            cout << "[+] SUCCESS: Windows SSH Service is now ACTIVE." << endl;
        } else {
            cout << "[+] ERROR: Service did not start. Dear user  Make sure installation finished." << endl;
        }

    #else
        // --- LINUX LOGIC (Standard Sudo / systemctl) ---
        cout << "[*] Checking SSH  service on linux ..." << endl;
        
        // xommand for checking and installing  (Debian/Ubuntu style)
        int check = system("dpkg -l | grep openssh-server >/dev/null 2>&1");
        
        if (check != 0) {
            cout << "[!] SSH Server missing. Installing via APT..." << endl;
            system("sudo apt-get update && sudo apt-get install -y openssh-server");
        }
        cout << "[*] Attempting to start SSH service...\n" << endl;
        if (system("sudo systemctl start ssh") == 0) {
           //chnage is runnng member 
            isRunning = true;
            //
            cout << "[+] SUCCESS: Linux SSH Daemon is now ACTIVE." << endl;
        } else {
            //error message 
            cout << "[+] ERROR: Could not start SSH service on Linux." << endl;
        }
    #endif
}
//service class ka method oveeride kia ha idhr commands are searcedh from google 
void scan()override{
    string command;
    cout<<"==================================\n";
    cout<<"         SYSTEM SCANNING SSH       \n";
    cout<<"===================================\n";
    #ifdef _WIN32
    //command for scaning sshservices on window  system 
    cout<<"[+] SCANNING ON WINDOWS\n";
    //commadn for windows system to scan ssh service on port 22 and listening state
    command="netstat -an|findstr \"LISTENING\" | findstr \":22\"";
    #else 
//command for scanning sshsevuce on linux system
  cout<<"[+] SCANNING ON LINUX\n";
    command="netstat -an | grep LISTEN | grep :22"  ;   
    #endif

    FILE* pipe=popen(command.c_str(),"r");
   if(!pipe){
    cout<<"[!] Command execution error\n";

   }
   cout<<"[+] SCANNING STARTED\n";
   char buffer[128];
   bool found=false;
   while(fgets(buffer ,sizeof(buffer) ,pipe) != nullptr)
{   found=true;
    cout<<"[FOUND]"<<buffer;
}
#ifdef _WIN32
//sleep mode is used to keep the screen helded for user 
_sleep(300);
#else 
u_sleep(3000);
#endif
pclose(pipe);
if(found){
    cout<<"[!] WARNING SSH PORT IS ACTIVE AND EXPOSED\n";

}

else 
cout<<"[!] SYSTEM IS SAFE\n";

cout<<"=====================================\n";
}
//isi class ka mehotd cpp file ma defibne krna a 
void bruteForceSimulate();

};
#endif
