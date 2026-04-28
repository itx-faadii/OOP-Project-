#include <iostream>
#include <string>
#include <list>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include "../headers/ActivityLogger.h"
#include "../headers/CredentialStore.h"
#include "../headers/MemoryModule.h"
#include "../headers/NETWORK.h"
#include "../headers/SERVICE.h"
#include "../headers/WorkStation.h"
#include "../headers/FIREWALL.h"
#include "../headers/DATABASESERVER.h"
#include "../headers/SSHService.h"
#include "../headers/HTTPService.h"

using namespace std;

class MenuManager {

private:
    Logger          logger;
    CredentialStore creds;
    MemoryModule    mem;
    Firewall        fw;
    WorkStation     ws;
    DatabaseServer  db;
    HTTPService     http;
    SSHService      ssh;

    void slowPrint(const string& msg) {
        cout << msg;
        cout.flush();
        #ifdef _WIN32
            _sleep(300);
        #else
            u_sleep(300000);
        #endif
    }

    void delay(int ms) {
        #ifdef _WIN32
            _sleep(ms);
        #else
            u_sleep(ms * 1000);
        #endif
    }

    void showBanner() {
        cout << "\n";
        cout << "================================================\n";
        cout << "         SHADOW-SHELL v1.0                      \n";
        cout << "         Network Security Simulator             \n";
        cout << "================================================\n";
        cout << "        For Educational Purposes Only           \n";
        cout << "================================================\n\n";
    }

    void showStartup() {
        slowPrint("[SYSTEM] Initializing SHADOW-SHELL");
        for (int i = 0; i < 3; i++) {
            delay(400);
            cout << ".";
            cout.flush();
        }
        cout << "\n[SYSTEM] All modules loaded successfully.\n";
        cout << "[+] Logger initialized.\n";
        cout << "[+] Network nodes online.\n";
        cout << "[+] Services ready.\n";
        logger.log("[STARTUP] SHADOW-SHELL launched.");
    }

    void showShutdown() {
        slowPrint("\n[SYSTEM] Shutting down SHADOW-SHELL");
        for (int i = 0; i < 3; i++) {
            delay(400);
            cout << ".";
            cout.flush();
        }
        logger.log("[SHUTDOWN] SHADOW-SHELL exited by user.");
        cout << "\n[GOODBYE] Stay safe!\n\n";
    }

    void showMainMenu() {
        cout << "\n============ MAIN MENU ============\n";
        cout << " [1] Testing & Diagnostics         \n";
        cout << " [2] Protection & Monitoring       \n";
        cout << " [3] Attack Simulation             \n";
        cout << " [4] Configure System              \n";
        cout << " [0] Exit                          \n";
        cout << "===================================\n";
        cout << "Enter choice: ";
    }

    void showTestingMenu() {
        cout << "\n===== TESTING & DIAGNOSTICS =====\n";
        cout << " [1] Check Network Node Status    \n";
        cout << " [2] Check Memory State           \n";
        cout << " [3] Check Password Strength      \n";
        cout << " [4] Show Credentials Summary     \n";
        cout << " [5] Scan HTTP Service            \n";
        cout << " [6] Scan SSH Service             \n";
        cout << " [7] Test Workstation Security    \n";
        cout << " [8] Test Database Vulnerability  \n";
        cout << " [9] Test Firewall Vulnerability  \n";
        cout << " [0] Back                         \n";
        cout << "==================================\n";
        cout << "Enter choice: ";
    }

    void showProtectionMenu() {
        cout << "\n===== PROTECTION & MONITORING =====\n";
        cout << " [1] View Activity Logs            \n";
        cout << " [2] Export Logs                   \n";
        cout << " [3] Clear Logs                    \n";
        cout << " [4] Update Software               \n";
        cout << " [5] Patch Vulnerabilities         \n";
        cout << " [6] Check Detection Level         \n";
        cout << " [7] Firewall - Allow Traffic      \n";
        cout << " [8] Firewall - Block Traffic      \n";
        cout << " [9] Firewall - Log Traffic        \n";
        cout << " [10] Firewall - Update Rules      \n";
        cout << " [11] WorkStation - Connect Node   \n";
        cout << " [12] WorkStation - Disconnect Node\n";
        cout << " [13] WorkStation - Send Data      \n";
        cout << " [14] WorkStation - Receive Data   \n";
        cout << " [15] Database - Store Data        \n";
        cout << " [16] Database - Backup            \n";
        cout << " [17] Database - Encrypt           \n";
        cout << " [18] Database - Decrypt           \n";
        cout << " [0] Back                          \n";
        cout << "====================================\n";
        cout << "Enter choice: ";
    }

    void showAttackMenu() {
        cout << "\n===== ATTACK SIMULATION =====\n";
        cout << " [1] Brute Force Attack       \n";
        cout << " [2] Buffer Overflow Test     \n";
        cout << " [3] HTTP Service Attack      \n";
        cout << " [4] SSH Service Attack       \n";
        cout << " [5] Firewall Data Flow Test  \n";
        cout << " [6] Stop HTTP Service        \n";
        cout << " [7] Stop SSH Service         \n";
        cout << " [0] Back                     \n";
        cout << "==============================\n";
        cout << "Enter choice: ";
    }

    void showConfigureMenu() {
        cout << "\n===== CONFIGURE SYSTEM =====\n";
        cout << " [1] Credentials Config     \n";
        cout << " [2] Memory Config          \n";
        cout << " [3] Logger Config          \n";
        cout << " [4] Firewall Config        \n";
        cout << " [5] Database Config        \n";
        cout << " [6] HTTP Service Config    \n";
        cout << " [7] SSH Service Config     \n";
        cout << " [8] Network Node Info      \n";
        cout << " [0] Back                   \n";
        cout << "============================\n";
        cout << "Enter choice: ";
    }

    void showCredConfigMenu() {
        cout << "\n--- Credentials Config ---\n";
        cout << " [1] Set Username          \n";
        cout << " [2] Set Password          \n";
        cout << " [3] Set Wordlist          \n";
        cout << " [4] Set Attempts          \n";
        cout << " [5] Get Username          \n";
        cout << " [6] Get Password          \n";
        cout << " [7] Get Wordlist          \n";
        cout << " [8] Get Attempts          \n";
        cout << " [9] Check Password        \n";
        cout << " [0] Back                  \n";
        cout << "--------------------------\n";
        cout << "Enter choice: ";
    }

    void showMemConfigMenu() {
        cout << "\n--- Memory Config ---\n";
        cout << " [1] Set Buffer Size    \n";
        cout << " [2] Get Buffer Size    \n";
        cout << " [3] Reset Memory       \n";
        cout << " [0] Back               \n";
        cout << "--------------------\n";
        cout << "Enter choice: ";
    }

    void showLoggerConfigMenu() {
        cout << "\n--- Logger Config ---\n";
        cout << " [1] Set Detection Level  \n";
        cout << " [2] Set Log File Path    \n";
        cout << " [3] Get Log Entries      \n";
        cout << " [4] Get Log File Path    \n";
        cout << " [0] Back                 \n";
        cout << "---------------------\n";
        cout << "Enter choice: ";
    }

    void showFirewallConfigMenu() {
        cout << "\n--- Firewall Config ---\n";
        cout << " [1] Set Rules           \n";
        cout << " [2] Set Log File        \n";
        cout << " [3] Get Rules           \n";
        cout << " [4] Get Log File        \n";
        cout << " [0] Back                \n";
        cout << "----------------------\n";
        cout << "Enter choice: ";
    }

    void showDBConfigMenu() {
        cout << "\n--- Database Config ---\n";
        cout << " [1] Set DB Name         \n";
        cout << " [2] Set Encrypted Flag  \n";
        cout << " [3] Set Backup Path     \n";
        cout << " [4] Get DB Name         \n";
        cout << " [5] Get Encrypted Flag  \n";
        cout << " [6] Get Backup Path     \n";
        cout << " [0] Back                \n";
        cout << "----------------------\n";
        cout << "Enter choice: ";
    }

    void showHTTPConfigMenu() {
        cout << "\n--- HTTP Service Config ---\n";
        cout << " [1] Set Request Count      \n";
        cout << " [2] Set HTTPS Flag         \n";
        cout << " [3] Get Request Count      \n";
        cout << " [4] Get HTTPS Flag         \n";
        cout << " [5] Get Port               \n";
        cout << " [6] Get Type               \n";
        cout << " [7] Get Name               \n";
        cout << " [8] Check If Active        \n";
        cout << " [0] Back                   \n";
        cout << "--------------------------\n";
        cout << "Enter choice: ";
    }

    void showSSHConfigMenu() {
        cout << "\n--- SSH Service Config ---\n";
        cout << " [1] Set Auth Attempts     \n";
        cout << " [2] Set Max Tries         \n";
        cout << " [3] Get Auth Attempts     \n";
        cout << " [4] Get Max Tries         \n";
        cout << " [5] Get Port              \n";
        cout << " [6] Get Type              \n";
        cout << " [7] Get Name              \n";
        cout << " [8] Check If Active       \n";
        cout << " [0] Back                  \n";
        cout << "-------------------------\n";
        cout << "Enter choice: ";
    }

    void showNodeInfoMenu() {
        cout << "\n--- Network Node Info ---\n";
        cout << " [1] Get Firewall ID          \n";
        cout << " [2] Get Firewall Name        \n";
        cout << " [3] Get WorkStation ID       \n";
        cout << " [4] Get WorkStation Name     \n";
        cout << " [5] Get Database ID          \n";
        cout << " [6] Get Database Name        \n";
        cout << " [7] Add Service to FW        \n";
        cout << " [8] Remove Service from FW   \n";
        cout << " [9] WorkStation Connected?   \n";
        cout << " [10] WorkStation ConnectedTo?\n";
        cout << " [0] Back                     \n";
        cout << "-------------------------\n";
        cout << "Enter choice: ";
    }

    void handleTesting() {
        int choice;
        do {
            showTestingMenu();
            cin >> choice;
            cin.ignore();

            if (choice == 1) {
                cout << "\n[INIT] Scanning Network Nodes...\n";
                cout << "================================\n";
                fw.scanSystem();
                cout << "\n";
                ws.scanSystem();
                logger.log("[TEST] Network nodes scanned for vulnerabilities.");
                cout << "[SUCCESS] Scan complete.\n";
            } else if (choice == 2) {
                cout << "\n[INIT] Checking Memory Module...\n";
                mem.showMemoryState();
                mem.detectOverflow();
                logger.log("[TEST] Memory state checked.");
            } else if (choice == 3) {
                string pass;
                cout << "Enter password to test: ";
                getline(cin, pass);
                creds.setPassword(pass);
                bool weak = creds.isWeak();
                if (weak) cout << "[!] WARNING: Password is WEAK\n";
                else      cout << "[+] Password strength is ACCEPTABLE\n";
                logger.log("[TEST] Password strength checked.");
            } else if (choice == 4) {
                cout << "\n[INIT] Displaying Credentials & Database Integrity...\n";
                cout << "================================\n";
                creds.display();
                cout << "\n[DB INFO] Checking database status...\n";
                string query = "*";
                db.retrieveData(query);
                cout << "[+] Database integrity verified.\n";
                logger.log("[TEST] Credentials and database displayed.");
            } else if (choice == 5) {
                cout << "\n[INIT] Scanning HTTP Service Vulnerabilities...\n";
                cout << "================================\n";
                http.scan();
                logger.log("[TEST] HTTP service scanned.");
            } else if (choice == 6) {
                cout << "\n[INIT] Scanning SSH Service Vulnerabilities...\n";
                cout << "================================\n";
                ssh.scan();
                logger.log("[TEST] SSH service scanned.");
            } else if (choice == 7) {
                cout << "\n[INIT] Testing Workstation Security...\n";
                cout << "================================\n";
                bool vuln = ws.isSecure();
                if (vuln) cout << "[!] WARNING: Workstation has vulnerabilities.\n";
                else      cout << "[+] Workstation appears secure.\n";
                logger.log("[TEST] Workstation security tested.");
            } else if (choice == 8) {
                cout << "\n[INIT] Testing Database Server Vulnerability...\n";
                cout << "================================\n";
                db.testVulnerability();
                logger.log("[TEST] Database vulnerability tested.");
            } else if (choice == 9) {
                cout << "\n[INIT] Testing Firewall Vulnerability...\n";
                cout << "================================\n";
                fw.testVulnerability();
                logger.log("[TEST] Firewall vulnerability tested.");
            }
        } while (choice != 0);
    }

    void handleProtection() {
        int choice;
        do {
            showProtectionMenu();
            cin >> choice;
            cin.ignore();

            if (choice == 1) {
                cout << "\n[INIT] Loading Activity Logs...\n";
                logger.showlogs();
            } else if (choice == 2) {
                string path;
                cout << "Enter export path (or press Enter for default): ";
                getline(cin, path);
                logger.exportLogs(path);
                cout << "[+] Logs exported successfully.\n";
            } else if (choice == 3) {
                cout << "[!] WARNING: This will DELETE all logs.\n";
                char confirm;
                cout << "Are you sure? (y/n): ";
                cin >> confirm;
                cin.ignore();
                if (confirm == 'y' || confirm == 'Y') {
                    logger.clearLogs();
                    cout << "[+] Logs cleared.\n";
                } else {
                    cout << "[CANCELLED] No changes made.\n";
                }
            } else if (choice == 4) {
                cout << "\n[INIT] Updating Software on Workstation...\n";
                ws.updateSoftware();
                logger.log("[PROTECTION] Software updated.");
            } else if (choice == 5) {
                cout << "\n[INIT] Patching Vulnerabilities...\n";
                ws.patchVulnerabilities();
                logger.log("[PROTECTION] Vulnerabilities patched.");
            } else if (choice == 6) {
                cout << "[INFO] Current Detection Level: " << logger.getDetectionLevel() << "\n";
            } else if (choice == 7) {
                string rule;
                cout << "Enter rule/port to ALLOW (e.g. 80 or SSH): ";
                getline(cin, rule);
                fw.allowTraffic(rule);
                logger.log("[PROTECTION] Firewall allowed traffic: " + rule);
            } else if (choice == 8) {
                string rule;
                cout << "Enter rule/port to BLOCK (e.g. 23 or Telnet): ";
                getline(cin, rule);
                fw.blockTraffic(rule);
                logger.log("[PROTECTION] Firewall blocked traffic: " + rule);
            } else if (choice == 9) {
                string info;
                cout << "Enter traffic info to log: ";
                getline(cin, info);
                fw.logTraffic(info);
                logger.log("[PROTECTION] Traffic logged to firewall log.");
            } else if (choice == 10) {
                list<string> newRules;
                string rule;
                cout << "Enter rules one by one (blank line to finish):\n";
                while (true) {
                    getline(cin, rule);
                    if (rule.empty()) break;
                    newRules.push_back(rule);
                }
                fw.updateRules(newRules);
                logger.log("[PROTECTION] Firewall rules updated.");
            } else if (choice == 11) {
                cout << "\n[INIT] Connecting WorkStation to Database Server...\n";
                ws.connectTo(&db);
                logger.log("[PROTECTION] WorkStation connected to DatabaseServer.");
            } else if (choice == 12) {
                cout << "\n[INIT] Disconnecting WorkStation...\n";
                ws.disconnect(&db);
                logger.log("[PROTECTION] WorkStation disconnected.");
            } else if (choice == 13) {
                string data;
                cout << "Enter data to send from WorkStation to Database: ";
                getline(cin, data);
                ws.sendData(data, &db);
                logger.log("[PROTECTION] WorkStation sent data to DatabaseServer.");
            } else if (choice == 14) {
                string data;
                cout << "Enter data to receive at WorkStation from Database: ";
                getline(cin, data);
                ws.receiveData(data, &db);
                logger.log("[PROTECTION] WorkStation received data from DatabaseServer.");
            } else if (choice == 15) {
                string data;
                cout << "Enter data to store in database: ";
                getline(cin, data);
                db.storeData(data);
                logger.log("[PROTECTION] Data stored in database.");
            } else if (choice == 16) {
                cout << "\n[INIT] Starting Database Backup...\n";
                db.backupDatabase();
                logger.log("[PROTECTION] Database backed up.");
            } else if (choice == 17) {
                cout << "\n[INIT] Encrypting Database...\n";
                db.encryptData();
                logger.log("[PROTECTION] Database encrypted.");
            } else if (choice == 18) {
                cout << "\n[INIT] Decrypting Database...\n";
                db.decryptData();
                logger.log("[PROTECTION] Database decrypted.");
            }
        } while (choice != 0);
    }

    void handleAttack() {
        int choice;
        do {
            showAttackMenu();
            cin >> choice;
            cin.ignore();

            if (choice == 1) {
                cout << "\n[!] INITIATING BRUTE FORCE ATTACK...\n";
                cout << "================================\n";
                creds.loadDefultWordlist();
                creds.bruteForceAttack(logger);
                logger.incrementDetectionLevel();
                cout << "[!] Attack logged. Detection Level Increased.\n";
            } else if (choice == 2) {
                cout << "\n[!] TESTING BUFFER OVERFLOW VULNERABILITY...\n";
                cout << "================================\n";
                string input;
                cout << "Enter payload to overflow buffer: ";
                getline(cin, input);
                mem.writeData(input, logger);
                logger.incrementDetectionLevel();
                if (mem.isOverflowDetected())
                    cout << "[!] OVERFLOW SUCCESSFUL - System Compromised!\n";
            } else if (choice == 3) {
                cout << "\n[!] TESTING WEB SERVICE VULNERABILITIES...\n";
                cout << "================================\n";
                cout << "\n[STEP 1] Starting HTTP Service...\n";
                http.execute();
                cout << "\n[STEP 2] Scanning for open ports...\n";
                http.scan();
                cout << "\n[STEP 3] Injecting malicious payload...\n";
                http.injectPayloadSimulate();
                logger.incrementDetectionLevel();
                logger.log("[ATTACK] Web service attack attempted.");
            } else if (choice == 4) {
                cout << "\n[!] TESTING SSH SERVICE VULNERABILITIES...\n";
                cout << "================================\n";
                cout << "\n[STEP 1] Starting SSH Service...\n";
                ssh.execute();
                cout << "\n[STEP 2] Scanning SSH Port...\n";
                ssh.scan();
                cout << "\n[STEP 3] SSH Brute Force Simulation...\n";
                ssh.bruteForceSimulate();
                logger.incrementDetectionLevel();
                logger.log("[ATTACK] SSH brute force attack attempted.");
            } else if (choice == 5) {
                cout << "\n[!] FIREWALL DATA FLOW ANALYSIS...\n";
                cout << "================================\n";
                fw.checkDataFlow();
                logger.incrementDetectionLevel();
                logger.log("[ATTACK] Firewall data flow analysis attempted.");
            } else if (choice == 6) {
                cout << "\n[!] STOPPING HTTP SERVICE...\n";
                cout << "================================\n";
                http.stop();
                logger.log("[ATTACK] HTTP service stopped.");
            } else if (choice == 7) {
                cout << "\n[!] STOPPING SSH SERVICE...\n";
                cout << "================================\n";
                ssh.stop();
                logger.log("[ATTACK] SSH service stopped.");
            }
        } while (choice != 0);
    }

    void handleCredConfig() {
        int sub;
        do {
            showCredConfigMenu();
            cin >> sub;
            cin.ignore();

            if (sub == 1) {
                string val;
                cout << "Enter new username: ";
                getline(cin, val);
                creds.setUsername(val);
                cout << "[+] Username updated.\n";
                logger.log("[CONFIG] Credentials username set.");
            } else if (sub == 2) {
                string val;
                cout << "Enter new password: ";
                getline(cin, val);
                creds.setPassword(val);
                cout << "[+] Password updated.\n";
                logger.log("[CONFIG] Credentials password set.");
            } else if (sub == 3) {
                list<string> wl;
                string word;
                cout << "Enter words one by one (blank to finish):\n";
                while (true) {
                    getline(cin, word);
                    if (word.empty()) break;
                    wl.push_back(word);
                }
                creds.setWordlist(wl);
                cout << "[+] Wordlist updated.\n";
                logger.log("[CONFIG] Credentials wordlist set.");
            } else if (sub == 4) {
                int val;
                cout << "Enter attempts count: ";
                cin >> val;
                cin.ignore();
                creds.setAttempts(val);
                cout << "[+] Attempts updated.\n";
                logger.log("[CONFIG] Credentials attempts set.");
            } else if (sub == 5) {
                cout << "[INFO] Username: " << creds.getUsername() << "\n";
            } else if (sub == 6) {
                cout << "[INFO] Password: " << creds.getPassword() << "\n";
            } else if (sub == 7) {
                list<string> wl = creds.getWordlist();
                cout << "[INFO] Wordlist (" << wl.size() << " entries):\n";
                for (const string& w : wl) cout << "  - " << w << "\n";
            } else if (sub == 8) {
                cout << "[INFO] Attempts: " << creds.getAttempts() << "\n";
            } else if (sub == 9) {
                string attempt;
                cout << "Enter password to check: ";
                getline(cin, attempt);
                if (creds.checkPassword(attempt)) cout << "[+] Password MATCHED.\n";
                else                              cout << "[!] Password did NOT match.\n";
                logger.log("[CONFIG] Password check performed.");
            }
        } while (sub != 0);
    }

    void handleMemConfig() {
        int sub;
        do {
            showMemConfigMenu();
            cin >> sub;
            cin.ignore();

            if (sub == 1) {
                int val;
                cout << "Enter new buffer size: ";
                cin >> val;
                cin.ignore();
                mem.setBufferSize(val);
                cout << "[+] Buffer size updated.\n";
                logger.log("[CONFIG] Memory buffer size set.");
            } else if (sub == 2) {
                cout << "[INFO] Buffer Size: " << mem.getBufferSize() << "\n";
            } else if (sub == 3) {
                mem.reset();
                cout << "[+] Memory reset done.\n";
                logger.log("[CONFIG] Memory module reset.");
            }
        } while (sub != 0);
    }

    void handleLoggerConfig() {
        int sub;
        do {
            showLoggerConfigMenu();
            cin >> sub;
            cin.ignore();

            if (sub == 1) {
                int val;
                cout << "Enter detection level: ";
                cin >> val;
                cin.ignore();
                logger.setDetectionLevel(val);
                cout << "[+] Detection level updated.\n";
            } else if (sub == 2) {
                string val;
                cout << "Enter log file path: ";
                getline(cin, val);
                logger.setLogFilePath(val);
                cout << "[+] Log file path updated.\n";
            } else if (sub == 3) {
                list<string> entries = logger.getLogEntries();
                cout << "[INFO] Log Entries (" << entries.size() << "):\n";
                for (const string& e : entries) cout << "  " << e << "\n";
            } else if (sub == 4) {
                cout << "[INFO] Log File Path: " << logger.getLogFilePath() << "\n";
            }
        } while (sub != 0);
    }

    void handleFirewallConfig() {
        int sub;
        do {
            showFirewallConfigMenu();
            cin >> sub;
            cin.ignore();

            if (sub == 1) {
                list<string> rules;
                string rule;
                cout << "Enter rules one by one (blank to finish):\n";
                while (true) {
                    getline(cin, rule);
                    if (rule.empty()) break;
                    rules.push_back(rule);
                }
                fw.setRules(rules);
                cout << "[+] Firewall rules set.\n";
                logger.log("[CONFIG] Firewall rules configured.");
            } else if (sub == 2) {
                string val;
                cout << "Enter log file name: ";
                getline(cin, val);
                fw.setLogFiles(val);
                cout << "[+] Firewall log file set.\n";
                logger.log("[CONFIG] Firewall log file configured.");
            } else if (sub == 3) {
                list<string> rules = fw.getRules();
                cout << "[INFO] Firewall Rules (" << rules.size() << "):\n";
                for (const string& r : rules) cout << "  - " << r << "\n";
            } else if (sub == 4) {
                cout << "[INFO] Firewall Log File: " << fw.getLogFiles() << "\n";
            }
        } while (sub != 0);
    }

    void handleDBConfig() {
        int sub;
        do {
            showDBConfigMenu();
            cin >> sub;
            cin.ignore();

            if (sub == 1) {
                string val;
                cout << "Enter new DB name: ";
                getline(cin, val);
                db.setDbName(val);
                cout << "[+] DB name updated.\n";
                logger.log("[CONFIG] Database name set.");
            } else if (sub == 2) {
                char val;
                cout << "Set encrypted? (y/n): ";
                cin >> val;
                cin.ignore();
                db.setIsEncrypted(val == 'y' || val == 'Y');
                cout << "[+] Encrypted flag updated.\n";
                logger.log("[CONFIG] Database encryption flag set.");
            } else if (sub == 3) {
                string val;
                cout << "Enter backup path: ";
                getline(cin, val);
                db.setBackupPath(val);
                cout << "[+] Backup path updated.\n";
                logger.log("[CONFIG] Database backup path set.");
            } else if (sub == 4) {
                cout << "[INFO] DB Name: " << db.getDbName() << "\n";
            } else if (sub == 5) {
                cout << "[INFO] Is Encrypted: " << (db.getIsEncrypted() ? "YES" : "NO") << "\n";
            } else if (sub == 6) {
                cout << "[INFO] Backup Path: " << db.getBackupPath() << "\n";
            }
        } while (sub != 0);
    }

    void handleHTTPConfig() {
        int sub;
        do {
            showHTTPConfigMenu();
            cin >> sub;
            cin.ignore();

            if (sub == 1) {
                int val;
                cout << "Enter request count: ";
                cin >> val;
                cin.ignore();
                http.setRequestCount(val);
                cout << "[+] Request count updated.\n";
                logger.log("[CONFIG] HTTP request count set.");
            } else if (sub == 2) {
                char val;
                cout << "Is HTTPS? (y/n): ";
                cin >> val;
                cin.ignore();
                http.setIsHTTPS(val == 'y' || val == 'Y');
                cout << "[+] HTTPS flag updated.\n";
                logger.log("[CONFIG] HTTP HTTPS flag set.");
            } else if (sub == 3) {
                cout << "[INFO] Request Count: " << http.getRequestCount() << "\n";
            } else if (sub == 4) {
                cout << "[INFO] Is HTTPS: " << (http.getIsHTTPS() ? "YES" : "NO") << "\n";
            } else if (sub == 5) {
                cout << "[INFO] Port: " << http.getPort() << "\n";
            } else if (sub == 6) {
                cout << "[INFO] Type: " << http.getType() << "\n";
            } else if (sub == 7) {
                cout << "[INFO] Name: " << http.getName() << "\n";
            } else if (sub == 8) {
                cout << "[INFO] Is Active: " << (http.isActive() ? "YES" : "NO") << "\n";
            }
        } while (sub != 0);
    }

    void handleSSHConfig() {
        int sub;
        do {
            showSSHConfigMenu();
            cin >> sub;
            cin.ignore();

            if (sub == 1) {
                int val;
                cout << "Enter auth attempts: ";
                cin >> val;
                cin.ignore();
                ssh.setAuthAttempts(val);
                cout << "[+] Auth attempts updated.\n";
                logger.log("[CONFIG] SSH auth attempts set.");
            } else if (sub == 2) {
                int val;
                cout << "Enter max tries: ";
                cin >> val;
                cin.ignore();
                ssh.setMaxTries(val);
                cout << "[+] Max tries updated.\n";
                logger.log("[CONFIG] SSH max tries set.");
            } else if (sub == 3) {
                cout << "[INFO] Auth Attempts: " << ssh.getAuthAttempts() << "\n";
            } else if (sub == 4) {
                cout << "[INFO] Max Tries: " << ssh.getMaxTries() << "\n";
            } else if (sub == 5) {
                cout << "[INFO] Port: " << ssh.getPort() << "\n";
            } else if (sub == 6) {
                cout << "[INFO] Type: " << ssh.getType() << "\n";
            } else if (sub == 7) {
                cout << "[INFO] Name: " << ssh.getName() << "\n";
            } else if (sub == 8) {
                cout << "[INFO] Is Active: " << (ssh.isActive() ? "YES" : "NO") << "\n";
            }
        } while (sub != 0);
    }

    void handleNodeInfo() {
        int sub;
        do {
            showNodeInfoMenu();
            cin >> sub;
            cin.ignore();

            if (sub == 1) {
                cout << "[INFO] Firewall ID: " << fw.getId() << "\n";
            } else if (sub == 2) {
                cout << "[INFO] Firewall Name: " << fw.getName() << "\n";
            } else if (sub == 3) {
                cout << "[INFO] WorkStation ID: " << ws.getId() << "\n";
            } else if (sub == 4) {
                cout << "[INFO] WorkStation Name: " << ws.getName() << "\n";
            } else if (sub == 5) {
                cout << "[INFO] Database ID: " << db.getId() << "\n";
            } else if (sub == 6) {
                cout << "[INFO] Database Name: " << db.getName() << "\n";
            } else if (sub == 7) {
                fw.addService(&http);
                cout << "[+] HTTP Service added to Firewall.\n";
                logger.log("[CONFIG] HTTP service added to Firewall node.");
            } else if (sub == 8) {
                fw.removeService(&http);
                cout << "[+] HTTP Service removed from Firewall.\n";
                logger.log("[CONFIG] HTTP service removed from Firewall node.");
            } else if (sub == 9) {
                cout << "[INFO] WorkStation Connected: " << (ws.getIsConnected() ? "YES" : "NO") << "\n";
            } else if (sub == 10) {
                NetworkNode* node = ws.getConnectedTo();
                if (node != nullptr) cout << "[INFO] WorkStation Connected To: " << node->getName() << "\n";
                else                 cout << "[INFO] WorkStation is not connected to any node.\n";
            }
        } while (sub != 0);
    }

    void handleConfigure() {
        int choice;
        do {
            showConfigureMenu();
            cin >> choice;
            cin.ignore();

            if      (choice == 1) handleCredConfig();
            else if (choice == 2) handleMemConfig();
            else if (choice == 3) handleLoggerConfig();
            else if (choice == 4) handleFirewallConfig();
            else if (choice == 5) handleDBConfig();
            else if (choice == 6) handleHTTPConfig();
            else if (choice == 7) handleSSHConfig();
            else if (choice == 8) handleNodeInfo();

        } while (choice != 0);
    }

public:
    MenuManager()
        : creds("admin", "1234"),
          mem(32),
          fw(1, "Firewall-01", list<Service*>(), list<string>(), ""),
          ws(2, "WorkStation-01", list<Service*>(), false, nullptr),
          db(3, "Database-Server", list<Service*>(), "../db/shadow_db.txt", false, ""),
          http(443, "HTTPS", "WebServer", 0, true),
          ssh(22, "SSH", "SSHServer", 0, 5)
    {}

    void run() {
        showBanner();
        showStartup();

        int choice;
        do {
            showMainMenu();
            cin >> choice;
            cin.ignore();

            if      (choice == 1) handleTesting();
            else if (choice == 2) handleProtection();
            else if (choice == 3) handleAttack();
            else if (choice == 4) handleConfigure();
            else if (choice == 0) showShutdown();

        } while (choice != 0);
    }
};