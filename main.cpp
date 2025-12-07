#include "SkyNet.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// ============ UTILITY FUNCTIONS ============
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void clearInputBuffer() {
    char c;
    while (cin.get(c) && c != '\n') {}
}

bool isDigit(char c) {
    return (c >= '0' && c <= '9');
}

void pauseScreen() {
    cout << "\n(Press Enter to continue...)";
    cin.get();
}

int getValidInt(string prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        cout << prompt << " [" << minVal << "-" << maxVal << "]: ";
        cin >> value;

        if (cin.fail()) {
            cin.clear();
            clearInputBuffer();
            cout << "    [!] Error: Please enter a valid number!\n";
        }
        else if (value < minVal || value > maxVal) {
            clearInputBuffer();
            cout << "    [!] Error: Value must be between " << minVal << " and " << maxVal << "!\n";
        }
        else {
            clearInputBuffer();
            return value;
        }
    }
}

string getValidString(string prompt) {
    string input;
    while (true) {
        cout << prompt << ": ";
        cin >> input;

        bool isNumeric = true;
        for (size_t i = 0; i < input.length(); i++) {
            if (!isDigit(input[i])) {
                isNumeric = false;
                break;
            }
        }

        if (isNumeric) {
            cout << "    [!] Error: Cannot be purely numeric!\n";
            clearInputBuffer();
        }
        else {
            clearInputBuffer();
            return input;
        }
    }
}

void displayWelcomeScreen() {
    clearScreen();
    cout << "\n\n";
    cout << "  ========================================================\n";
    cout << "                    SKYNET ATC SIMULATOR                  \n";
    cout << "            Air Traffic Control System v2.0               \n";
    cout << "  ========================================================\n\n";
    cout << "              Managing the skies with precision...\n\n";
    cout << "              Initializing System.....\n\n";
    cout << "              > Graph Module Loaded\n";
    cout << "              > Min-Heap Priority Queue Ready\n";
    cout << "              > Hash Table Registry Online\n";
    cout << "              > AVL Tree Logger Active\n";
    cout << "              > Collision Detection Armed\n\n";
    cout << "  ========================================================\n\n";
    cout << "                  Press ENTER to continue...";
    cin.get();
}

void displayExitScreen() {
    clearScreen();
    cout << "\n\n\n";
    cout << "  ========================================================\n";
    cout << "                                                          \n";
    cout << "          SHUTTING DOWN SKYNET ATC SYSTEM...              \n";
    cout << "                                                          \n";
    cout << "  ========================================================\n\n";
    cout << "              Saving flight data... Done!\n";
    cout << "              Closing radar systems... Done!\n";
    cout << "              Securing communication channels... Done!\n\n";
    cout << "  ========================================================\n";
    cout << "                                                          \n";
    cout << "       Thank you for using SkyNet ATC System!             \n";
    cout << "              All flights safely managed.                 \n";
    cout << "                                                          \n";
    cout << "  ========================================================\n\n";
}

// ============ MAIN FUNCTION ============
int main() {
    displayWelcomeScreen();

    SkyNet system;
    int mainChoice;

    // Initialize default locations
    system.addLocation("JFK", 'A', 2, 2);
    system.addLocation("LHR", 'A', 15, 18);
    system.addLocation("DXB", 'A', 10, 10);
    system.addLocation("WaypointAlpha", 'W', 8, 8);
    system.addLocation("WaypointBeta", 'W', 12, 12);

    // Initialize routes
    system.addRoute(0, 3, 100);
    system.addRoute(3, 4, 150);
    system.addRoute(4, 1, 200);
    system.addRoute(0, 2, 180);
    system.addRoute(2, 1, 220);

    while (true) {
        clearScreen();

        cout << "\n========================================================\n";
        cout << "         SKYNET ATC SIMULATOR - MAIN MENU              \n";
        cout << "========================================================\n\n";

        cout << "  [1] Airspace Visualizer\n";
        cout << "      - View radar, current flights, and landing queue\n\n";

        cout << "  [2] Flight Control\n";
        cout << "      - Add, move, land, and manage emergency flights\n\n";

        cout << "  [3] Search & Reporting\n";
        cout << "      - Search flights, view logs, find safe routes\n\n";

        cout << "  [4] Data Management\n";
        cout << "      - Save/Load system state\n\n";

        cout << "  [5] Exit System\n\n";

        cout << "========================================================\n";

        mainChoice = getValidInt("Select Category", 1, 5);

        // ========== MENU 1: AIRSPACE VISUALIZER ==========
        if (mainChoice == 1) {
            clearScreen();
            cout << "\n=== AIRSPACE VISUALIZER ===\n";

            cout << "\n[Current Airspace Status]\n";
            system.displayRadar();

            cout << "\n[Landing Queue Status]\n";
            system.displayNextToLand();

            pauseScreen();
        }

        // ========== MENU 2: FLIGHT CONTROL ==========
        else if (mainChoice == 2) {
            clearScreen();
            cout << "\n=== FLIGHT CONTROL ===\n";

            cout << "\n  [1] Add New Flight\n";
            cout << "  [2] Move Existing Flight\n";
            cout << "  [3] Declare Emergency\n";
            cout << "  [4] Process Landing (Next in Queue)\n";
            cout << "  [5] View All Active Flights\n";
            cout << "  [6] Update Flight Details\n";
            cout << "  [7] Back to Main Menu\n\n";

            int sub = getValidInt("Select Option", 1, 7);

            if (sub == 1) {
                cout << "\n--- ADD NEW FLIGHT ---\n";

                string id = getValidString("Flight ID (e.g., PK786)");
                int p = getValidInt("Priority Level", 1, 4);

                cout << "\n  Priority Guide:\n";
                cout << "  1 = CRITICAL (Emergency/Hijack)\n";
                cout << "  2 = HIGH (Low Fuel <10%)\n";
                cout << "  3 = MEDIUM (Passenger)\n";
                cout << "  4 = LOW (Cargo/Private)\n\n";

                string stat = getValidString("Status (e.g., Approaching)");
                int x = getValidInt("X Coordinate", 0, 19);
                int y = getValidInt("Y Coordinate", 0, 19);
                string mod = getValidString("Aircraft Model (e.g., Boeing737)");
                string org = getValidString("Origin Airport (e.g., JFK)");
                string dst = getValidString("Destination Airport (e.g., LHR)");
                int fuel = getValidInt("Fuel Percentage", 0, 100);

                system.requestLanding(id, p, stat, x, y, mod, org, dst, fuel);
            }
            else if (sub == 2) {
                cout << "\n--- MOVE FLIGHT ---\n";

                string id = getValidString("Flight ID to Move");
                int newX = getValidInt("New X Coordinate", 0, 19);
                int newY = getValidInt("New Y Coordinate", 0, 19);

                system.moveFlight(id, newX, newY);
            }
            else if (sub == 3) {
                cout << "\n--- DECLARE EMERGENCY ---\n";

                string id = getValidString("Flight ID");
                system.emergencyOverride(id);
            }
            else if (sub == 4) {
                cout << "\n--- PROCESS LANDING ---\n";

                system.processLanding();
            }
            else if (sub == 5) {
                cout << "\n--- ALL ACTIVE FLIGHTS ---\n";

                system.displayAllFlights();
            }
            else if (sub == 6) {
                cout << "\n--- UPDATE FLIGHT DETAILS ---\n";
                cout << "  [1] Update Fuel Level\n";
                cout << "  [2] Update Route\n";
                cout << "  [3] Update All Details\n";

                int updateChoice = getValidInt("Select Update Type", 1, 3);
                string id = getValidString("Flight ID");

                if (updateChoice == 1) {
                    int newFuel = getValidInt("New Fuel Level (%)", 0, 100);
                    system.updateFuelLevel(id, newFuel);
                }
                else if (updateChoice == 2) {
                    string newOrig = getValidString("New Origin");
                    string newDest = getValidString("New Destination");
                    system.updatePosition(id, newOrig, newDest);
                }
                else if (updateChoice == 3) {
                    string model = getValidString("Aircraft Model");
                    string orig = getValidString("Origin");
                    string dest = getValidString("Destination");
                    int fuel = getValidInt("Fuel %", 0, 100);
                    system.updateAircraft(id, model, orig, dest, fuel);
                }
            }

            pauseScreen();
        }

        // ========== MENU 3: SEARCH & REPORTING ==========
        else if (mainChoice == 3) {
            clearScreen();
            cout << "\n=== SEARCH & REPORTING ===\n";

            cout << "\n  [1] Search Flight by ID\n";
            cout << "  [2] View Daily Flight Log\n";
            cout << "  [3] Calculate Safe Route to Airport\n";
            cout << "  [4] View All Locations\n";
            cout << "  [5] Back to Main Menu\n\n";

            int sub = getValidInt("Select Option", 1, 5);

            if (sub == 1) {
                cout << "\n--- SEARCH FLIGHT ---\n";

                string id = getValidString("Enter Flight ID");
                system.searchAircraftDetails(id);
            }
            else if (sub == 2) {
                cout << "\n--- DAILY FLIGHT LOG ---\n";

                system.displayFlightLog();
            }
            else if (sub == 3) {
                cout << "\n--- SAFE ROUTE CALCULATOR ---\n";

                system.listLocations();
                int id = getValidInt("Enter Current Location Node ID", 0, 49);
                system.findShortestPath(id);
            }
            else if (sub == 4) {
                cout << "\n--- ALL LOCATIONS ---\n";

                system.listLocations();
            }

            pauseScreen();
        }

        // ========== MENU 4: DATA MANAGEMENT ==========
        else if (mainChoice == 4) {
            clearScreen();
            cout << "\n=== DATA MANAGEMENT ===\n";

            cout << "\n  [1] Save System State\n";
            cout << "  [2] Load System State\n";
            cout << "  [3] Back to Main Menu\n\n";

            int sub = getValidInt("Select Option", 1, 3);

            if (sub == 1) {
                cout << "\n--- SAVING DATA ---\n";
                system.saveData();
            }
            else if (sub == 2) {
                cout << "\n--- LOADING DATA ---\n";
                system.loadData();
            }

            pauseScreen();
        }

        // ========== MENU 5: EXIT ==========
        else if (mainChoice == 5) {
            displayExitScreen();
            break;
        }
    }

    return 0;
}