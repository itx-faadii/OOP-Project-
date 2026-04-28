#include "../headers/HTTPService.h"
#include <unistd.h>
//setters 
void HTTPService::setRequestCount(int requestCount){
    this->requestCount=requestCount;
}
void HTTPService::setIsHTTPS(bool isHTTPS){
    this->isHTTPS=isHTTPS;
}
//getters
int HTTPService::getRequestCount()const{
    return this->requestCount;
}
bool HTTPService::getIsHTTPS()const{
    return this->isHTTPS;
}
//method of headr file 
void  HTTPService::injectPayloadSimulate() {
    if (!isRunning) {
        cout << "[X] ATTACK FAILED: Cannot inject payload into a closed port (443)." << endl;
        return;
    }

    cout << "\n[!] VULNERABILITY EXPLOIT: Initiating Payload Injection..." << endl;
    
    // Asli payloads jo hacker use karte hain
    string payloads[] = {
        "' OR '1'='1' --",               // SQL Injection (Bypass Login)
        "<script>alert('XSS')</script>", // XSS (Script Injection)
        "; rm -rf /",                    // Command Injection (Very Dangerous)
        "admin'--"                       // Auth Bypass
    };

    cout << "[*] Target URL: https://localhost:" << getPort() << "/login.php" << endl;
    cout << "--------------------------------------------------" << endl;

    for (int i = 0; i < 4; i++) {
        cout << "[SENDING PAYLOAD]: " << payloads[i] << " ... " << flush;

        // Real-time effect ke liye delay
        #ifdef _WIN32
            _sleep(1200); 
        #else
            u_sleep(1200000);
        #endif

        if (i == 0 || i == 3) {
            cout << " [SUCCESS]" << endl;
            cout << "[>>>] SERVER RESPONSE: Welcome Admin! (Authentication Bypassed)" << endl;
        } else if (i == 1) {
            cout << " [SUCCESS]" << endl;
            cout << "[>>>] SERVER RESPONSE: Script executed on client browser." << endl;
        } else {
            cout << " [FAILED]" << endl;
            cout << "[>>>] SERVER RESPONSE: 403 Forbidden (WAF Blocked Execution)" << endl;
        }
        cout << endl;
    }

    cout << "[!] ATTACK COMPLETE: System state might be compromised." << endl;
    cout << "--------------------------------------------------" << endl;
}
