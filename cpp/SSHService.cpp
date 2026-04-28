#include "../headers/SSHService.h"
#include <unistd.h>
//setters defination 
void SSHService::setAuthAttempts(int x){
    this->authAttempts=x;
}
void SSHService::setMaxTries(int x){
    this->maxTries=x;
}
//getters definition
int SSHService::getAuthAttempts()const{
    return this->authAttempts;
}
int SSHService::getMaxTries()const{
    return this->maxTries;
}
void SSHService::bruteForceSimulate() {
    // firstv testing thtat the serivce is active or not
    if (!isRunning) {
        cout << "[+] ATTACK ABORTED: Port " << getPort() << " is closed." << endl;
        return;
    }

    cout << "\n[!] INTRUSION DETECTED: Starting Brute Force on: " << getName() << "..." << endl;
    
    // some basic passwrds array 
    string passwords[] = {"admin", "12345", "root", "p@ssword", "ssh_admin"};
    string correctPass = "ssh_admin"; 
    bool success = false;

    //  Loop run till  max tries 
    for (int i = 0; i < maxTries; i++) {
        authAttempts = i + 1; // attaemot updated 

        cout << "[Attempt " << authAttempts << "]: Testing password '" << passwords[i % 5] << "'... " << flush;//flush keyword is used to print the output immediately without waiting for a newline character, it is used here to show the attempt number and password being tested in real-time as the brute-force simulation runs.

        // delay trick used 
        #ifdef _WIN32
            _sleep(800); // 0.8 seconds
        #else
            u_sleep(800000);
        #endif

        if (passwords[i % 5] == correctPass) {
            cout << "SUCCESS! [Access Granted]" << endl;
            success = true;
            break;
        } else {
            cout << "FAILED" << endl;
        }

        // 4. Security Logic: if attempts are increased it works as security 
        if (authAttempts >= 3) {
            cout << "[!] WARNING: Multiple failed attempts. Rate-limiting engaged..." << endl;
        }
    }

    //the Resukt 
    if (success) {
        cout << "===> NODE COMPROMISED: Hacker has gained control of " << getName() << endl;
    } else {
        cout << "===> ATTACK BLOCKED: " << getName() << " firewall dropped the connection." << endl;
    }
}
