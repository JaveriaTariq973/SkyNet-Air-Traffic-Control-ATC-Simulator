#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Aircraft.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct HashNode {
    string flightId;
    string model;
    string origin;
    string destination;
    int fuelLevel;
    HashNode* next;
};

class HashTable {
private:
    HashNode* aircraftRegistry[TABLE_SIZE];
    int hashFunction(string key);

public:
    HashTable();
    void registerAircraft(string id, string model, string orig, string dest, int fuel);
    void searchAircraftDetails(string flightId);

    // File I/O Helpers
    void saveRegistry(ofstream& out);
    void loadEntry(string id, string model, string orig, string dest, int fuel);
    //Update fuel level for a flight
        void updateFuelLevel(string flightId, int newFuel);

    // Update position for a flight
    void updatePosition(string flightId, string newOrigin, string newDestination);

    // Update complete aircraft details
    void updateAircraft(string flightId, string model, string orig, string dest, int fuel);
};

#endif#pragma once
