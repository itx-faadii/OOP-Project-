#ifndef WORKSTATION_H
#define WORKSTATION_H
#include"NETWORK.h"
#include<cstdio>
#include<iostream>
#include<cstdlib>
using namespace std;
class WorkStation:public NetworkNode{
    private:
    bool isConnected;
    NetworkNode* connectedTo;
    
    public:
    WorkStation(int id ,const string& name,list<Service*> newService,bool isConnected, NetworkNode* connectedTo):
    NetworkNode(id,name,newService),isConnected(isConnected),connectedTo(connectedTo){}
    WorkStation():NetworkNode(),isConnected(false),connectedTo(nullptr){}
    //objecct copy constructor also object slicing is used 
    WorkStation(const WorkStation& obj):NetworkNode(obj),isConnected(obj.isConnected),connectedTo(obj.connectedTo){}
    //setters
    void setIsConnected(bool isConnected);
    void setConnectedTo(NetworkNode* connectedTo);
    //getters 
    bool getIsConnected()const;
    
    NetworkNode* getConnectedTo()const;
    //methods
    void connectTo(NetworkNode* connectedTo); 
    void disconnect(NetworkNode* connectedTo);
    void sendData(const string& data, NetworkNode* destination);
    void receiveData(const string& data, NetworkNode* source);
    bool  isSecure( );
    
    
    //isi ka ha 
    void scanSystem() override {
    int choose;
    cout << "================================\n";
    cout << "       SCANNING WORKSTATION     \n";
    cout << "================================\n"; 
    cout << "ENTER YOUR CHOICE \n";
    cout << "1. For checking ports\n";
    cout << "2. For checking tasklists\n";
    cout << "3. For IP scan\n";
    cout << "4. For Configuration scan\n";
    cin >> choose;
    cin.ignore();

    string command;
    switch (choose) {
        case 1: // Port Scan
            #ifdef _WIN32
                command = "netstat -an | findstr \"LISTENING\"";
            #else
                command = "netstat -an | grep \"LISTENING\"";
            #endif
            break;
        case 2: // Tasklist
            #ifdef _WIN32
                command = "tasklist";
            #else
                command = "ps -aux";
            #endif
            break;
        case 3: // IP Scan
            #ifdef _WIN32
                command = "ipconfig /all";
            #else
                command = "ifconfig -a";
            #endif
            break;
        case 4: // Configuration Scan
            #ifdef _WIN32
                command = "systeminfo";
            #else
                command = "uname -a";
            #endif
            break;
        default:
            cout << "Invalid choice\n";
            return;
    }

    if (command.empty()) {
        cout << "Invalid choice\n";
        return;
    }

    cout << "\n[DETECTED OS] ";
    #ifdef _WIN32
        cout << "Windows\n";
    #else
        cout << "Linux\n";
    #endif
    
    cout << "[*] Running command: " << command << endl;
    cout << "================================\n";
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        cout << "! ERROR: Failed to run command\n";
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        cout << buffer;
    }
    pclose(pipe);

    cout << "================================\n";
    cout << "[+] Scan completed successfully\n";
}
//isi ka ha 
    void checkDataFlow() override {
        cout<<"[+]  Checking data flow in workstation....\n";
        cout<<"====================================\n";
        cout<<"[+] Data flow check in progress...\n";   
        cout<<"[+] Analyzing network traffic...\n";
        cout<<"====================================\n";
        
        string destinantion;
        cout<<"Enter the destination IP address or domain name: ";
        cin.ignore();
        getline(cin, destinantion);
        
        string command;
        #ifdef _WIN32
            cout<<"[DETECTED OS] Windows\n";
            cout<<"[*] Using Windows Terminal for data flow check...\n";
            command ="tracert " + destinantion;
        #else
            cout<<"[DETECTED OS] Linux\n";
            cout<<"[*] Using Linux Terminal for data flow check...\n";
            command ="traceroute " + destinantion;
        #endif
        
        cout<<"[*] Running command: " << command << "\n";
        cout<<"====================================\n";
        FILE* pipe=popen(command.c_str(),"r");
        if(!pipe){  
            cout<<"! ERROR: Failed to run command\n";
            return ;
        }
        char buffer[512];
        while(fgets(buffer,sizeof(buffer),pipe)!=nullptr){
            cout<<buffer;
        }
        pclose(pipe);
        cout<<"====================================\n";
        cout<<"[+] Data flow checked successfully \n";
    }
    //isi ka ha 
    void updateSoftware() override {
        cout<<"========================================\n";
        cout<<"[+]  Updating software in workstation....\n";
        cout<<"========================================\n";
        
        string softwareName;
        cout<<"Enter name of software to update: ";
        cin.ignore();
        getline(cin, softwareName);

        string command;
        #ifdef _WIN32
            cout<<"[DETECTED OS] Windows\n";
            cout<<"[*] Using Windows Package Manager...\n";
            command = "winget upgrade --id " + softwareName;
        #else
            cout<<"[DETECTED OS] Linux\n";
            cout<<"[*] Using APT Package Manager...\n";
            command = "sudo apt-get update && sudo apt-get install --only-upgrade -y " + softwareName;
        #endif
        
        cout<<"[*] Running command: " << command << "\n";
        cout<<"========================================\n";
        int result = system(command.c_str());
        cout<<"========================================\n";
        
        if(result == 0){
            cout<<"[+] Update command executed successfully \n";
        }
        else{
            cout<<"[!] ERROR: Failed to execute update command\n";
        }
    }
//isi ka ha 
void patchVulnerabilities() override {
    int osChoice;
    cout << "\n==========================================" << endl;
    cout << "  SHIELD-VIP: ADVANCED SECURITY PATCHER   " << endl;
    cout << "==========================================" << endl;
    cout << "Select Target OS:\n1. Windows (WinGet/SFC)\n2. Linux (APT/Kernel)\nChoice: ";
    cin >> osChoice;

    if (osChoice == 1) {
        // Windows-specific patching sequence
        cout << "\n[INIT] Starting Windows Security Audit & Repair" << endl;

        // Step 1: Scan & Upgrade applications using Winget
        cout << "\n[+] Upgrading outdated/vulnerable apps (Winget)..." << endl;
        if (system("where winget >nul 2>&1") != 0) {
            cout << "[!] Winget is not installed. Skipping App Patching.\n";
        } else {
            // Hum return nahi karenge, sirf koshish karenge apps update karne ki
            system("winget upgrade --all"); 
            cout << "[+] App update sequence completed." << endl;
        }

        // Step 2: Repair system file integrity using SFC
        cout << "\n[+] Repairing System File Integrity (SFC)..." << endl;
        cout << "[NOTE!] This may take 10-15 minutes. Please do not close the terminal." << endl;
        
        // '/scannow' use kiya hai taake jo violations mili thi wo theek ho jayein
        int result = system("sfc /scannow"); 
        
        if (result == 0) {
            cout << "\n[SUCCESS] System files repaired and verified." << endl;
        } else {
            cout << "\n[!] SFC found issues. If it failed, please run as Administrator." << endl;
        }

        cout << "\n[DONE] Windows Attack Surface has been reduced." << endl;
    } 
    else if (osChoice == 2) {
        // Linux-specific patching sequence
        cout << "\n[+] Launching Linux Hardening Sequence..." << endl;

        cout << "[+] Refreshing Security Repositories..." << endl;
        system("sudo apt-get update");

        cout << "\n[+] Patching Known Vulnerabilities (CVEs)..." << endl;
        system("sudo apt-get upgrade -y");

        cout << "\n[+] Cleaning up orphaned vulnerable packages..." << endl;
        system("sudo apt-get autoremove -y");

        cout << "\n[DONE] Linux Kernel & Apps are now patched." << endl;
    } 
    else {
        cout << "\n[!] Invalid Selection. Security Scan Aborted." << endl;
    }
    cout << "==========================================\n" << endl;
}

virtual ~WorkStation(){}


};


#endif
