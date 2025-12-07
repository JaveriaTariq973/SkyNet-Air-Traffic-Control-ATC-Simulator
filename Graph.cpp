#include "Graph.h"

Graph::Graph() {
    nodeCount = 0;
    for (int i = 0; i < MAX_NODES; i++) adjList[i] = nullptr;
}

void Graph::addLocation(string name, char type, int x, int y) {
    if (nodeCount >= MAX_NODES) return;
    locations[nodeCount] = { nodeCount, name, type, x, y };
    nodeCount++;
}

void Graph::addRoute(int srcId, int destId, int weight) {
    if (srcId >= nodeCount || destId >= nodeCount) return;
    AdjListNode* newNode = new AdjListNode;
    newNode->destId = destId;
    newNode->weight = weight;
    newNode->next = adjList[srcId];
    adjList[srcId] = newNode;
}

void Graph::listLocations() {
    cout << "\n--- Node List ---\n";
    for (int i = 0; i < nodeCount; i++) {
        cout << "ID " << i << ": " << locations[i].name << " (" << locations[i].type << ")\n";
    }
}

void Graph::displayRadar(Flight* planes, int planeCount) {
    char grid[GRID_SIZE][GRID_SIZE];
    // Init Grid
    for (int i = 0; i < GRID_SIZE; i++)
        for (int j = 0; j < GRID_SIZE; j++)
            grid[i][j] = '.';

    // Draw Locations
    for (int i = 0; i < nodeCount; i++) {
        if (locations[i].x < GRID_SIZE && locations[i].y < GRID_SIZE)
            grid[locations[i].x][locations[i].y] = locations[i].type;
    }

    // Draw Planes (From Heap)
    for (int i = 0; i < planeCount; i++) {
        if (planes[i].x < GRID_SIZE && planes[i].y < GRID_SIZE)
            grid[planes[i].x][planes[i].y] = 'P';
    }

    // Print
    cout << "\n========= SKYNET RADAR =========\n   ";
    for (int j = 0; j < GRID_SIZE; j++) cout << j % 10 << " ";
    cout << "\n";
    for (int i = 0; i < GRID_SIZE; i++) {
        cout << setw(2) << i << " [";
        for (int j = 0; j < GRID_SIZE; j++) cout << grid[i][j] << " ";
        cout << "]";
        if (i == 0) cout << " < A: Airport";
        if (i == 1) cout << " < P: Plane";
        if (i == 2) cout << " < W: Waypoint";
        cout << endl;
    }
    cout << "================================\n";
}

void Graph::printPathRecursive(int parent[], int j) {
    if (parent[j] == -1) { cout << locations[j].name; return; }
    printPathRecursive(parent, parent[j]);
    cout << " -> " << locations[j].name;
}

void Graph::findShortestPath(int startId) {
    int dist[MAX_NODES];
    int parent[MAX_NODES];
    bool visited[MAX_NODES];

    for (int i = 0; i < MAX_NODES; i++) {
        dist[i] = INF; parent[i] = -1; visited[i] = false;
    }
    dist[startId] = 0;

    for (int count = 0; count < nodeCount; count++) {
        int u = -1; int minVal = INF;
        for (int i = 0; i < nodeCount; i++) {
            if (!visited[i] && dist[i] < minVal) {
                minVal = dist[i]; u = i;
            }
        }
        if (u == -1 || dist[u] == INF) break;
        visited[u] = true;

        AdjListNode* temp = adjList[u];
        while (temp) {
            int v = temp->destId;
            if (!visited[v] && dist[u] + temp->weight < dist[v]) {
                dist[v] = dist[u] + temp->weight;
                parent[v] = u;
            }
            temp = temp->next;
        }
    }

    int nearestAirport = -1;
    int minDist = INF;
    for (int i = 0; i < nodeCount; i++) {
        if (locations[i].type == 'A' && dist[i] < minDist) {
            minDist = dist[i];
            nearestAirport = i;
        }
    }

    cout << "\n> SAFE ROUTE CALCULATION:\n";
    if (nearestAirport == -1) cout << "  No reachable airport found!\n";
    else {
        cout << "  Nearest Airport: " << locations[nearestAirport].name << endl;
        cout << "  Total Distance: " << minDist << " km\n  Path: ";
        printPathRecursive(parent, nearestAirport);
        cout << "\n";
    }
}