#include "../headers/CredentialStore.h"
//setters
void CredentialStore::setUsername(const string& username){
    this->username=username;
}
void CredentialStore::setPassword(const string& password){
    this->password=password;
}
void CredentialStore::setWordlist(const list<string>& wordlist){
    this->wordlist=wordlist;
}
void CredentialStore::setAttempts(int attempts){
    this->attempts=attempts;
}
//getters
string CredentialStore::getUsername()const{
    return this->username;
}
string CredentialStore::getPassword()const{
    return this->password;
}
            
list<string> CredentialStore::getWordlist()const{
    return this->wordlist   ;
}   
int CredentialStore::getAttempts()const{
    return this->attempts;
}
//methods
#include <fstream>

void CredentialStore::loadDefultWordlist() {
    string path;
    cout << "[?] Enter path to password list (or press Enter for defaults): ";
    getline(cin, path);

    bool fileLoaded = false;

    if (!path.empty()) {
        ifstream file(path); // Standard C++ file stream (fast & silent)
        if (file.is_open()) {
            string word;
            while (getline(file, word)) {
                if (!word.empty()) {
                    wordlist.push_back(word);
                    fileLoaded = true;
                }
            }
            file.close();
        }
    }

    if (!fileLoaded) {
        if (!path.empty()) cout << "[!] Could not open file. ";
        cout << "Loading default weak passwords...\n";
        wordlist.push_back("admin");
        wordlist.push_back("123456");
        wordlist.push_back("password");
        wordlist.push_back("root");
    }

    cout << "[SUCCESS] Wordlist loaded with " << wordlist.size() << " entries." << endl;
}
bool CredentialStore::checkPassword(const string& attempt) {
    attempts++;
    return (attempt == password);
}

void CredentialStore::bruteForceAttack(const Logger& logger) {
    // Convertible logic to make it compatible
//c++ allow us to change thuis 
//direct approch used 
    Logger& self = const_cast<Logger&>(logger);
    
    self.log("{+} PRO BRUTE FORCE INITIATED \n");
    bool found = false;

    // Advanced Loop for Wordlist i learnt from goole 
    for (const auto& guess : wordlist) {
        cout << "[ATTEMPTING]: " << guess << "... ";
        cout.flush(); // Forces text to show before the result is known
//fush use is lye kia q k cout line execte kr k phir show krta but zbrdasti ly letaha 
//real logic to chechk pasword         
if (checkPassword(guess)) {
            cout << "MATCH FOUND!\n";
            string successMsg = "SUCCESS: Cracked " + username + " with " + guess;
            
            // pipe logic smart way tp print hint taken from goole 
            string cmd;
            #ifdef _WIN32
                cmd = "echo " + successMsg + " >> \"" + self.getLogFilePath() + "\"";
                _pclose(_popen(cmd.c_str(), "w"));
            #else
                cmd = "echo \"" + successMsg + "\" >> \"" + self.getLogFilePath() + "\"";
                pclose(popen(cmd.c_str(), "w"));
            #endif
            
            found = true;
            break;
        } else {
            cout << "FAILED\n";
            cout.flush(); // Makes the "FAILED" text appear instantly
            
            // Log the failure silently using OS pipe
            string failMsg = "Attempt Failed for " + username + ": " + guess;
            #ifdef _WIN32
                _pclose(_popen(("echo " + failMsg + " >> \"" + self.getLogFilePath() + "\"").c_str(), "w"));
            #else
                pclose(popen(("echo \"" + failMsg + "\" >> \"" + self.getLogFilePath() + "\"").c_str(), "w"));
            #endif
        }
    }

    if (!found) {
        cout << "\n[!] All attempts finished. Brute force failed.\n";
        self.log("Brute force exhausted without success.");
    }
}
//this is standard logic to check password strength AND I DIRECT TAKE FROM GOOGLE DOCUMENT 
bool CredentialStore::isWeak() {
    int specialCharCount = 0;
    bool hasCapital = false;
    int length = password.length();

    for (char c : password) {
        if (isupper(c)) hasCapital = true;
        if (ispunct(c)) specialCharCount++; // Checks for symbols like !, @, #, $, etc.
    }

    // Logical Evaluation
    if (length >= 8 && specialCharCount >= 2 && hasCapital) {
        cout << "[INFO] Password Strength: STRONG\n";
        return false; // Not weak
    } 
    else if (length >= 8 && specialCharCount >= 2 && !hasCapital) {
        cout << "[INFO] Password Strength: NORMAL (Missing Capital Letter)\n";
        return false; 
    } 
    else {
        cout << "[WARNING] Password Strength: WEAK\n";
        return true; 
    }
}
void CredentialStore::display() {
    cout << "\n==============================\n";
    cout << "   USER CREDENTIAL SUMMARY    \n";
    cout << "==============================\n";
    cout << "Username       : " << username << "\n";
    cout << "Total Attempts : " << attempts << "\n";
    
    // Using our new logic
    bool weakStatus = isWeak();
    cout << "Security Status: " << (weakStatus ? "VULNERABLE" : "PROTECTED") << "\n";
    cout << "==============================\n";
}
