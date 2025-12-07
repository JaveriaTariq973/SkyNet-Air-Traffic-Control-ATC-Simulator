#pragma once
#ifndef MINHEAP_H
#define MINHEAP_H

#include "Aircraft.h"
#include <iostream>
#include <string>

using namespace std;

class MinHeap {
private:
    Flight landingHeap[MAX_FLIGHTS];
    int heapSize;

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    MinHeap();

    // Returns true if collision, false if safe
    bool checkCollision(int x, int y, string incomingId);

    void insert(string id, int prio, string stat, int x, int y);
    Flight extractMin();
    void emergencyOverride(string flightId);
    void displayNextToLand();

    int getSize();
    Flight* getFlightsArray(); // Needed for Radar
    // Move a flight to new coordinates
    bool moveFlight(string flightId, int newX, int newY);

    // Display all current flights with positions
    void displayAllFlights();
};

#endif