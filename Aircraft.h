#pragma once
// Aircraft.h
#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <string>
using namespace std;

// --- GLOBAL CONSTANTS ---
const int MAX_NODES = 50;
const int MAX_FLIGHTS = 50;
const int TABLE_SIZE = 30;
const int GRID_SIZE = 20;
const int INF = 9999999;

// --- SHARED STRUCT ---
// Used by MinHeap (for priority) and Graph (for Radar visualization)
struct Flight {
    string id;
    int priority;
    string status;
    int x, y;
};

#endif