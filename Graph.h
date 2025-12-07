#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include "Aircraft.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct Location {
    int id;
    string name;
    char type;
    int x, y;
};

struct AdjListNode {
    int destId;
    int weight;
    AdjListNode* next;
};

class Graph {
private:
    Location locations[MAX_NODES];
    AdjListNode* adjList[MAX_NODES];
    int nodeCount;

    void printPathRecursive(int parent[], int j);

public:
    Graph();
    void addLocation(string name, char type, int x, int y);
    void addRoute(int srcId, int destId, int weight);
    void listLocations();
    // Takes planes from Heap to draw them on the map
    void displayRadar(Flight* planes, int planeCount);
    void findShortestPath(int startId);
};

#endif