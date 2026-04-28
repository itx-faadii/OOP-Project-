#include "../headers/WorkStation.h"
void WorkStation::setIsConnected(bool isConnected){
    this->isConnected=isConnected;
}
void WorkStation::setConnectedTo(NetworkNode* connectedTo){
    this->connectedTo=connectedTo;
}
bool WorkStation::getIsConnected()const{
    return this->isConnected;
}
NetworkNode* WorkStation::getConnectedTo()const{
    return this->connectedTo;
}   
void WorkStation::connectTo(NetworkNode* connectedTo){
    if(connectedTo==nullptr){
        cout<<"! WARNING: Cannot connect to null node\n";
        return ;
    }
    setConnectedTo(connectedTo);
    setIsConnected(true);
    cout<<"Connected to "<<connectedTo->getName()<<" successfully \n";
}
void WorkStation::disconnect(NetworkNode* connectedTo){
    if(this->connectedTo==nullptr){
        cout<<"! Warning cannot connect to null node\n";
     return;
    }
    if(this->connectedTo != connectedTo){
        cout<<"! Warning: Not connected to "<<connectedTo->getName()<<"\n";
         return;        
    }
        this->setConnectedTo(nullptr);
        this->setIsConnected(false);
        cout<<"Disconnected from "<<connectedTo->getName()<<" successfully \n"; 
    
}
void WorkStation::sendData(const string& data, NetworkNode* destination){
    if(!getIsConnected()){
        cout<<"! Warning: Not connected to any node\n";
        return ;
    }
    if (destination == nullptr) {
        cout << "! Warning: Destination node is null\n";
        return;
    }

    if (getConnectedTo() != destination) {
        cout << "! Warning: Not connected to the specified destination node\n";
        return;
    }
    cout<<"Sending data\""<<data<<"\" to "<<destination->getName()<<"...\n";
    cout<<"Data sent successfully \n";
}
void WorkStation::receiveData(const string& data, NetworkNode* source){
    if(!getIsConnected()){
        cout<<"! Warning: Not connected to any node\n";
        return ;
    }
    if (source == nullptr) {
        cout << "! Warning: Source node is null\n";
        return;
    }

    if (getConnectedTo() != source) {
        cout << "! Warning: Not connected to the specified source node\n";
        return;
    }
    cout<<"Receiving data\""<<data<<"\" from "<<source->getName()<<"...\n";
    cout<<"Data received successfully \n";
}

bool WorkStation::isSecure(){
    cout << "[+] Starting vulnerability test on workstation only for Windows OS ...\n";

    // Check for open ports
    cout << "[STEP 1] Scanning for open ports...\n";
    string command = "netstat -an | findstr LISTENING"; // Windows example
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        cout << "[!] ERROR: Failed to execute port scan command.\n";
        return true; // Assume vulnerable if scan fails
    }

    char buffer[128];
    bool openPortsFound = false;
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        openPortsFound = true;
        cout << buffer; // Print open ports
    }
    pclose(pipe);

    if (openPortsFound) {
        cout << "[!] Vulnerability detected: Open ports found.\n";
        return true;
    }

    // Check for outdated software
    cout << "[STEP 2] Checking for outdated software...\n";
    command = "winget upgrade --all --check-only"; // Windows example
    int result = system(command.c_str());
    if (result != 0) {
        cout << "[!] Vulnerability detected: Outdated software found.\n";
        return true;
    }

    // Check for weak configurations
    cout << "[STEP 3] Checking for weak configurations...\n";
    command = "systeminfo | findstr /C:\"Hotfix\""; // Windows example
    pipe = popen(command.c_str(), "r");
    if (!pipe) {
        cout << "[!] ERROR: Failed to execute configuration check command.\n";
        return true; // Assume vulnerable if scan fails
    }

    bool weakConfigFound = false;
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        weakConfigFound = true;
        cout << buffer; // Print weak configurations
    }
    pclose(pipe);

    if (weakConfigFound) {
        cout << "[!] Vulnerability detected: Weak configurations found.\n";
        return true;
    }

    cout << "[+] No vulnerabilities detected. Workstation is secure.\n";
    return false;
}
