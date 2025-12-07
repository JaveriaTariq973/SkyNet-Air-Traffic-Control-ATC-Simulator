#include "SkyNet.h"

SkyNet::SkyNet() {
    systemClock = 800; 
}

// --- Module A ---
void SkyNet::addLocation(string name, char type, int x, int y) {
    graph.addLocation(name, type, x, y);
}
void SkyNet::addRoute(int srcId, int destId, int weight) {
    graph.addRoute(srcId, destId, weight);
}
void SkyNet::listLocations() {
    graph.listLocations();
}
void SkyNet::displayRadar() {
    // Graph draws the map, but needs plane info from Heap
    graph.displayRadar(heap.getFlightsArray(), heap.getSize());
}
void SkyNet::findShortestPath(int startId) {
    graph.findShortestPath(startId);
}

// --- Module B ---
bool SkyNet::requestLanding(string id, int prio, string stat, int x, int y, string model, string orig, string dest, int fuel) {
    // 1. Check Collision (Heap Logic)
    if (heap.checkCollision(x, y, id)) {
        cout << "    Flight Request Denied.\n";
        return false;
    }

    // 2. Add to Heap
    heap.insert(id, prio, stat, x, y);

    // 3. Register (Hash Logic)
    registry.registerAircraft(id, model, orig, dest, fuel);

    cout << "> Flight " << id << " added to Queue.\n";
    return true;
}

void SkyNet::processLanding() {
    if (heap.getSize() == 0) { cout << "No flights waiting.\n"; return; }

    Flight f = heap.extractMin();
    cout << "\n> LANDING " << f.id << " ... SUCCESS.\n";

    // Mod D: Log to AVL
    string logStatus = (f.priority == 1) ? "EMERGENCY LANDING" : "Landed Safely";
    logs.addLog(systemClock, f.id, logStatus);

    systemClock += 15;
    if (systemClock % 100 >= 60) systemClock = (systemClock / 100 + 1) * 100;
}

void SkyNet::emergencyOverride(string flightId) {
    heap.emergencyOverride(flightId);
}

void SkyNet::displayNextToLand() {
    heap.displayNextToLand();
}

// --- Module C ---
void SkyNet::searchAircraftDetails(string flightId) {
    registry.searchAircraftDetails(flightId);
}

// --- Module D ---
void SkyNet::displayFlightLog() {
    logs.displayLogs();
}

// --- System ---
void SkyNet::saveData() {
    ofstream out("skynet_data.txt");
    if (!out) { cout << "Error saving file.\n"; return; }

    out << "REGISTRY_START" << endl;
    registry.saveRegistry(out);
    out << "REGISTRY_END" << endl;

    out << "LOGS_START" << endl;
    logs.saveLogs(out);
    out << "LOGS_END" << endl;

    out.close();
    cout << "> System State Saved to 'skynet_data.txt'.\n";
}

void SkyNet::loadData() {
    ifstream in("skynet_data.txt");
    if (!in) { cout << "No save file found.\n"; return; }

    string line;
    while (in >> line) {
        if (line == "REGISTRY_START") {
            while (in >> line && line != "REGISTRY_END") {
                string m, o, d; int f;
                in >> m >> o >> d >> f;
                // Directly calling internal registry logic
                registry.registerAircraft(line, m, o, d, f);
            }
        }
        else if (line == "LOGS_START") {
            int t; string id, st;
            while (in >> t && in >> id && in >> st) {
                logs.addLog(t, id, st);
            }
        }
    }
    in.close();
    cout << "> Data Loaded Successfully.\n";
}
void SkyNet::moveFlight(string id, int newX, int newY) {
    heap.moveFlight(id, newX, newY);
}

void SkyNet::displayAllFlights() {
    heap.displayAllFlights();
}

void SkyNet::updateFuelLevel(string id, int fuel) {
    registry.updateFuelLevel(id, fuel);
}

void SkyNet::updatePosition(string id, string orig, string dest) {
    registry.updatePosition(id, orig, dest);
}

void SkyNet::updateAircraft(string id, string model, string orig, string dest, int fuel) {
    registry.updateAircraft(id, model, orig, dest, fuel);
}