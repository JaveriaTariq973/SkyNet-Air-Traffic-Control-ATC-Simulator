#include "MinHeap.h"

MinHeap::MinHeap() { heapSize = 0; }

void MinHeap::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (landingHeap[parent].priority > landingHeap[index].priority) {
            Flight temp = landingHeap[index];
            landingHeap[index] = landingHeap[parent];
            landingHeap[parent] = temp;
            index = parent;
        }
        else break;
    }
}

void MinHeap::heapifyDown(int index) {
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;
        if (left < heapSize && landingHeap[left].priority < landingHeap[smallest].priority) 
            smallest = left;
        if (right < heapSize && landingHeap[right].priority < landingHeap[smallest].priority)
            smallest = right;
        if (smallest == index) break;
        Flight temp = landingHeap[index];
        landingHeap[index] = landingHeap[smallest];
        landingHeap[smallest] = temp;
        index = smallest;
    }
}

bool MinHeap::checkCollision(int x, int y, string incomingId) {
    for (int i = 0; i < heapSize; i++) {
        if (landingHeap[i].x == x && landingHeap[i].y == y) {
            cout << "\n[!] COLLISION WARNING: Sector (" << x << "," << y << ") occupied by " << landingHeap[i].id << "!\n";
            return true;
        }
    }
    return false;
}

void MinHeap::insert(string id, int prio, string stat, int x, int y) {
    if (heapSize >= MAX_FLIGHTS) { cout << "Airspace Full!\n"; return; }
    landingHeap[heapSize] = { id, prio, stat, x, y };
    heapifyUp(heapSize);
    heapSize++;
}

Flight MinHeap::extractMin() {
    if (heapSize == 0) return { "", -1, "", -1, -1 }; // Empty indicator
    Flight f = landingHeap[0];
    landingHeap[0] = landingHeap[heapSize - 1];
    heapSize--;
    heapifyDown(0);
    return f;
}

void MinHeap::emergencyOverride(string flightId) {
    int idx = -1;
    for (int i = 0; i < heapSize; i++) {
        if (landingHeap[i].id == flightId) { idx = i; break; }
    }
    if (idx == -1) { cout << "Flight not found.\n"; return; }

    cout << "> EMERGENCY DECLARED FOR " << flightId << "! Priority set to 1.\n";
    landingHeap[idx].priority = 1;
    landingHeap[idx].status = "EMERGENCY";
    heapifyUp(idx);
}

void MinHeap::displayNextToLand() {
    if (heapSize == 0) cout << "Next to Land: [None]\n";
    else cout << "Next to Land: " << landingHeap[0].id << " [Status: " << landingHeap[0].status << "]\n";
}

int MinHeap::getSize() { return heapSize; }
Flight* MinHeap::getFlightsArray() { return landingHeap; }
bool MinHeap::moveFlight(string flightId, int newX, int newY) {
    // Find the flight
    int idx = -1;
    for (int i = 0; i < heapSize; i++) {
        if (landingHeap[i].id == flightId) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        cout << "Flight not found in airspace.\n";
        return false;
    }

    // Check collision at new position
    if (checkCollision(newX, newY, flightId)) {
        return false;
    }

    // Update position
    landingHeap[idx].x = newX;
    landingHeap[idx].y = newY;
    cout << "> Flight " << flightId << " moved to (" << newX << ", " << newY << ")\n";
    return true;
}

void MinHeap::displayAllFlights() {
    if (heapSize == 0) {
        cout << "\nNo flights currently in airspace.\n";
        return;
    }

    cout << "\n=== CURRENT FLIGHTS IN AIRSPACE ===\n";
    cout << "ID         | Priority | Status      | Position\n";
    cout << "----------------------------------------------\n";

    for (int i = 0; i < heapSize; i++) {
        cout << landingHeap[i].id;
        // Padding for alignment
        for (int j = landingHeap[i].id.length(); j < 11; j++) cout << " ";

        cout << "| " << landingHeap[i].priority << "        | ";
        cout << landingHeap[i].status;
        for (int j = landingHeap[i].status.length(); j < 12; j++) cout << " ";

        cout << "| (" << landingHeap[i].x << ", " << landingHeap[i].y << ")\n";
    }
    cout << "==========================================\n";
}