#include "../headers/DATABASESERVER.h"
//stters 
void DatabaseServer::setDbName(const string& dbName){
    this->dbName=dbName;
}
void DatabaseServer::setIsEncrypted(bool isEncrypted){
    this->isEncrypted=isEncrypted;
}
void DatabaseServer::setBackupPath(const string& backupPath){
    this->backupPath=backupPath;
}
//getters
string DatabaseServer::getDbName()const{
    return this->dbName;
}
bool DatabaseServer::getIsEncrypted()const{
    return this->isEncrypted;
}
string DatabaseServer::getBackupPath()const{
    return this->backupPath;
}
// 1. DATA STORE KARNA (File mein write karna)
void DatabaseServer::storeData(const string& data) {
    cout << "[+] Storing data in database: " << dbName << "..." << endl;
    // Simple logic: Data ko ek text file mein append karna
    FILE* file = fopen(dbName.c_str(), "a"); 
    if (file) {
        fprintf(file, "%s\n", data.c_str());
        fclose(file);
        cout << ">>> Data saved successfully." << endl;
    } else {
        cout << ">>> ERROR: Database file not accessible." << endl;
    }
}

// 2. DATA RETRIEVE KARNA (File se read karna)
void DatabaseServer::retrieveData(const string& query) {
    cout << "[?] Searching for: " << query << " in " << dbName << "..." << endl;
    string command;
    #ifdef _WIN32
        command = "findstr /i \"" + query + "\" " + dbName;
    #else
        command = "grep -i \"" + query + "\" " + dbName; // Linux standard
    #endif
    
    if (system(command.c_str()) != 0) {
        cout << ">>> No records found matching the query." << endl;
    }
}

// 3. BACKUP DATABASE (File copy karna)
void DatabaseServer::backupDatabase() {
    cout << "[!] Starting Backup Process..." << endl;
    string command;
    #ifdef _WIN32
        command = "copy " + dbName + " " + backupPath;
    #else
        command = "cp " + dbName + " " + backupPath;
    #endif
    
    if (system(command.c_str()) == 0) {
        cout << ">>> Backup created successfully at: " << backupPath << endl;
    } else {
        cout << ">>> ERROR: Backup failed. Check paths." << endl;
    }
}

// 4. ENCRYPT DATA (File ko 'Hidden' aur 'Read-only' karna - Simple Logic)
void DatabaseServer::encryptData() {
    cout << "[*] Encrypting (Protecting) Database file..." << endl;
    #ifdef _WIN32
        // Windows command: File ko hidden (+h) aur system (+s) file bana dena
        string command = "attrib +h +s +r " + dbName;
    #else
        // Linux: File name ke shuru mein dot (.) laga dena
        string command = "mv " + dbName + " ." + dbName;
    #endif
    
    if (system(command.c_str()) == 0) {
        isEncrypted = true;
        cout << ">>> Database is now protected/encrypted." << endl;
    }
}

// 5. DECRYPT DATA (Attributes wapis normal karna)
void DatabaseServer::decryptData() {
    cout << "[*] Decrypting (Unprotecting) Database file..." << endl;
    #ifdef _WIN32
        string command = "attrib -h -s -r " + dbName;
    #else
        string command = "mv ." + dbName + " " + dbName;
    #endif
    
    if (system(command.c_str()) == 0) {
        isEncrypted = false;
        cout << ">>> Database is now decrypted and accessible." << endl;
    }
}
