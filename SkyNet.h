#ifndef SKYNET_H
#define SKYNET_H

#include "Graph.h"
#include "MinHeap.h"
#include "HashTable.h"
#include "AVLTree.h"
#include <iostream>
#include <fstream>

using namespace std;

class SkyNet {
private:
    Graph graph;
    MinHeap heap;
    HashTable registry;
    AVLTree logs;
    int systemClock;

public:
    SkyNet();

    // Module A Wrappers
    void addLocation(string name, char type, int x, int y);
    void addRoute(int srcId, int destId, int weight);
    void listLocations();
    void displayRadar();
    void findShortestPath(int startId);

    // Module B Wrappers
    bool requestLanding(string id, int prio, string stat, int x, int y, string model, string orig, string dest, int fuel);
    void processLanding();
    void emergencyOverride(string flightId);
    void displayNextToLand();

    // Module C Wrappers
    void searchAircraftDetails(string flightId);

    // Module D Wrappers
    void displayFlightLog();

    // System Wrappers
    void saveData();
    void loadData();
    void moveFlight(string id, int newX, int newY);

    // Display all flights wrapper
    void displayAllFlights();

    // Hash table update wrappers
    void updateFuelLevel(string id, int fuel);
    void updatePosition(string id, string orig, string dest);
    void updateAircraft(string id, string model, string orig, string dest, int fuel);
};

#endif