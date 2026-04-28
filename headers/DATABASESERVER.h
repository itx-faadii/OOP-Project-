#ifndef DATABASESERVER_H
#define DATABASESERVER_H
#include "NETWORK.h" 
#include<cstdio>
#include<iostream>
#include<cstdlib>

using namespace std;
class DatabaseServer:public NetworkNode{
    private:
    string dbName;
    bool isEncrypted;
    string backupPath;
    public:
    DatabaseServer(int id ,const string& name,const list<Service*> newService,const string& dbName,bool isEncrypted,const string& backupPath):
    NetworkNode(id,name,newService),dbName(dbName),isEncrypted(isEncrypted),backupPath(backupPath){}
    DatabaseServer():NetworkNode(),dbName(""),isEncrypted(false),backupPath(""){}       
    DatabaseServer(const DatabaseServer& obj):NetworkNode(obj),dbName(obj.dbName),isEncrypted(obj.isEncrypted),backupPath(obj.backupPath){}
    //setters   
    void setDbName(const string& dbName);
    void setIsEncrypted(bool isEncrypted);
    void setBackupPath(const string& backupPath);
    //getters
    string getDbName()const;
    bool getIsEncrypted()const;
    string getBackupPath()const;
    //methods
    void storeData(const string& data);
    void retrieveData(const string& query);
    void backupDatabase();
        void encryptData();
        void decryptData();
  void checkDataFlow() override {
    cout << "[+]  Checking data flow in DataBaseServer....\n";
    cout << "====================================\n";
    cout << "[+] Data flow check in progress...\n";   
    cout << "[+] Analyzing network traffic...\n";
    cout << "=====================================\n";

    string command;
    string destinantion; // destination 

    cout << "Enter the destination IP address or domain name: ";
    cin >> destinantion;

    #ifdef _WIN32
        // Windows commands 
        cout << "Using Windows Terminal for data flow check...\n";
        command = "tracert " + destinantion;
    #else
        // Linux Logic
        cout << "Using Linux Terminal for data flow check...\n";
        command = "traceroute " + destinantion;
    #endif

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {  
        cout << "! ERROR: Failed to run command\n";
        return;
    }

    char buffer[512]; // buffer size  reaidng chars 
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        cout << buffer;
    }
    pclose(pipe);

    cout << "Data flow checked successfully \n";
}

    //isi ka ha 
    void updateSoftware() override {
    cout << "========================================\n";
    cout << "[+] Updating software in workstation....\n";
    cout << "========================================\n";

    string listCommand;
    #ifdef _WIN32
        // Windows par update-able softwares ki list
        listCommand = "winget upgrade";
    #else
        // Linux par list of upgradable packages
        listCommand = "apt list --upgradable";
    #endif

    cout << "[*] Fetching available updates... Please wait.\n";
    system(listCommand.c_str()); // Pehle list dikhayi

    cout << "\n----------------------------------------\n";
    cout << "Enter name/ID of software to update from the list above: ";
    string softwareName;
    cin >> softwareName;

    string updateCommand;
    #ifdef _WIN32
        updateCommand = "winget upgrade --id " + softwareName;
    #else
        updateCommand = "sudo apt-get install --only-upgrade -y " + softwareName;
    #endif

    cout << "[*] Updating " << softwareName << "...\n";
    int result = system(updateCommand.c_str());
    
    if (result == 0) {
        cout << "[+] Software updated successfully!\n";
    }
    else {
        cout << "[!] ERROR: Failed to execute update command. Check spelling or admin rights.\n";
    }
}

//isi ka ha 
void patchVulnerabilities() override {
    cout << "\n==========================================" << endl;
    cout << " SHIELD-VIP: ADVANCED SECURITY PATCHER " << endl;
    cout << "==========================================" << endl;

    #ifdef _WIN32
        // --- Windows-specific patching sequence  check 
        //cout << "[+] DETECTED OS: Windows" << endl;
        cout << "[INIT] Starting Windows Security Audit..." << endl;

        //  Scan & Upgrade apps
        cout << "[+] Scanning for outdated/vulnerable apps via Winget..." << endl;
        if (system("where winget >nul 2>&1") != 0) //null approach is lye use ki ha ta k user ko falto outputs nze n aye 
        {
            cout << "[!] Winget is not installed on this system.\n";
        } else {
            if (system("winget upgrade --all") != 0) {
                cout << "[!] Failed to upgrade apps using Winget.\n";
            }
        }

        // System File Checker    y thek krta ha system ke files ko scan krta ha aur agar koi file corrupt ya missing hoti ha to usy thek krta ha
         cout << "\n[+] Verifying System File Integrity (SFC)..." << endl;
        if (system("sfc /verifyonly") != 0) {
            cout << "[!] System File Checker encountered an error (Needs Admin).\n";
        } else {
            cout << "[DONE] Windows Attack Surface has been reduced." << endl;
        }

    #else
        // --- Linux-specific patching sequence   
        //cout << "[+] DETECTED OS: Linux" << endl;
        cout << "[INIT] Launching Linux Hardening Sequence..." << endl;

        //  Update Repos on linux  iska aur koi kam nai ha y bs refresh krta ha 
        cout << "[+] Refreshing Security Repositories..." << endl;
        if (system("sudo apt-get update") != 0) {
            cout << "[!] Failed to refresh repositories.\n";
        } else {
            //  Upgrade Packages on linux  asli upgrade is command st hoga 
            cout << "\n[+] Patching Known Vulnerabilities (CVEs)..." << endl;
            if (system("sudo apt-get upgrade -y") != 0) {
                cout << "[!] Failed to upgrade packages.\n";
            }

            //  Cleanup
            cout << "\n[+] Cleaning up orphaned vulnerable packages..." << endl;
            if (system("sudo apt-get autoremove -y") != 0) {
                cout << "[!] Failed to clean up orphaned packages.\n";
            } else {
                cout << "\n[DONE] Linux Kernel & Apps are now patched." << endl;
            }
        }
    #endif

    cout << "==========================================\n" << endl;
}
void testVulnerability() override {
    cout << "--- Checking Database Server Security ---" << endl;

    #ifdef _WIN32
        // --- Windows Logic ---
        cout << "[+] DETECTED OS: Windows" << endl;

        //  Open Ports
        cout << "[STEP 1] Scanning for open ports...\n";
        if (system("netstat -an | findstr LISTENING") == 0) { 
            cout << "[!] Vulnerability detected: Listening ports found.\n";
        } else {
            cout << "[+] No listening ports detected.\n";
        }

        //  Outdated Software
        cout << "[STEP 2] Checking for outdated software...\n";
        if (system("winget upgrade --check-only >nul 2>&1") == 0) {
            cout << "[!] Vulnerability detected: Outdated software found.\n";
        } else {
            cout << "[+] All software is up-to-date.\n";
        }

        //  Hotfixes/Security Patches
        cout << "[STEP 3] Checking for security hotfixes...\n";
        if (system("systeminfo | findstr /C:\"Hotfix\" >nul 2>&1") != 0) {
            cout << "[!] Vulnerability detected: No Hotfix information found.\n";
        } else {
            cout << "[+] Security hotfixes are present.\n";
        }

    #else
        // --- Linux Logic ---
        cout << "[+] DETECTED OS: Linux" << endl;

        //  Open Ports (Using ss or netstat)
        cout << "[STEP 1] Scanning for open ports...\n";
        if (system("ss -tuln | grep LISTEN > /dev/null 2>&1") == 0) {
            cout << "[!] Vulnerability detected: Open listening ports found.\n";
        } else {
            cout << "[+] No open ports detected.\n";
        }

        //  Outdated Packages
        cout << "[STEP 2] Checking for upgradable packages...\n";
        if (system("apt list --upgradable 2>/dev/null | grep -v 'Listing...' | grep . > /dev/null 2>&1") == 0) {
            cout << "[!] Vulnerability detected: Outdated packages found.\n";
        } else {
            cout << "[+] All packages are up-to-date.\n";
        }

        //  Kernel/System Config  update cnfrimationn 
        cout << "[STEP 3] Checking system security state...\n";
        if (system("uname -v | grep -i \"SMP\" > /dev/null 2>&1") == 0) {
            cout << "[+] System kernel is in standard state.\n";
        } else {
            cout << "[!] Warning: Non-standard kernel configuration detected.\n";
        }
    #endif

    cout << "--- Security Check Complete ---\n";
}

        virtual ~DatabaseServer(){}; 
};    
#endif
