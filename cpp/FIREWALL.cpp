#include "../headers/FIREWALL.h"
//setters 
void Firewall::setRules(const list<string> rules){
    this->rules=rules;
}
void Firewall::setLogFiles(const string& logFiles){
    this->logFiles=logFiles;
}   
//getters 
list<string> Firewall::getRules()const{
    return this->rules;
}
string Firewall::getLogFiles()const{
    return this->logFiles;
}
//methods 
// 1. ALLOW TRAFFIC LOGIC
void Firewall::allowTraffic(const string& ruleName) {
    cout << "[+] Attempting to ALLOW traffic: " << ruleName << endl;
    string command;
    

    #ifdef _WIN32
        // Windows: Specific rule name ko enable karna
        command = "netsh advfirewall firewall set rule name=\"" + ruleName + "\" new enable=yes";
    #else
        // Linux: ufw (Uncomplicated Firewall) ke zariye allow karna
        command = "sudo ufw allow " + ruleName;
    #endif

    if (system(command.c_str()) == 0) {
        cout << ">>> SUCCESS: Traffic allowed on system." << endl;
        rules.push_back(ruleName + " (Allowed)");
    } else {
        cout << ">>> ERROR: Operation failed. (Check Admin/Sudo rights)" << endl;
    }
}

// 2. BLOCK TRAFFIC LOGIC
void Firewall::blockTraffic(const string& ruleName) {
    cout << "[-] Attempting to BLOCK traffic: " << ruleName << endl;
    string command;

    #ifdef _WIN32
        // Windows: Rule ko disable ya block action mein dalna
        command = "netsh advfirewall firewall set rule name=\"" + ruleName + "\" new action=block";
    #else
        // Linux: ufw block command
        command = "sudo ufw deny " + ruleName;
    #endif

    if (system(command.c_str()) == 0) {
        cout << ">>> SUCCESS: Traffic blocked on system." << endl;
        rules.push_back(ruleName + " (Blocked)");
    } else {
        cout << ">>> ERROR: Operation failed." << endl;
    }
}

// 3. LOG TRAFFIC (Writing to Actual File)
void Firewall::logTraffic(const string& trafficInfo) {
    string fileName = logFiles.empty() ? "../logs/firewall_logs.txt" : logFiles;
    
    // fstream use kar ke file mein write karna
    FILE* file = fopen(fileName.c_str(), "a"); // 'a' for append mode
    if (file) {
        fprintf(file, "[LOG]: %s\n", trafficInfo.c_str());
        fclose(file);
        cout << "[+] Entry added to log file: " << fileName << endl;
    } else {
        cout << "[!] Failed to write to log file." << endl;
    }
}

// 4. UPDATE RULES
void Firewall::updateRules(const list<string>& newRules) {
    cout << "[*] Updating firewall rules list..." << endl;
    rules.clear();
    for (const string& r : newRules) {
        rules.push_back(r);
    }
    cout << "[+] Total rules updated: " << rules.size() << endl;
}
