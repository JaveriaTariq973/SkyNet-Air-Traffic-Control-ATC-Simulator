#include "HashTable.h"

HashTable::HashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) aircraftRegistry[i] = nullptr;
}

int HashTable::hashFunction(string key) {
    int sum = 0;
    for (char c : key) sum += c;
    return sum % TABLE_SIZE;
}

void HashTable::registerAircraft(string id, string model, string orig, string dest, int fuel) {
    int index = hashFunction(id);
    HashNode* newNode = new HashNode;
    newNode->flightId = id; newNode->model = model;
    newNode->origin = orig; newNode->destination = dest;
    newNode->fuelLevel = fuel; newNode->next = aircraftRegistry[index];
    aircraftRegistry[index] = newNode;
}

void HashTable::searchAircraftDetails(string flightId) {
    int index = hashFunction(flightId);
    HashNode* temp = aircraftRegistry[index];
    while (temp) {
        if (temp->flightId == flightId) {
            cout << "\n--- FLIGHT INFO ---\n";
            cout << "ID: " << temp->flightId << "\nModel: " << temp->model
                << "\nRoute: " << temp->origin << " -> " << temp->destination
                << "\nFuel: " << temp->fuelLevel << "%\n-------------------\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Flight not found in Registry.\n";
}

void HashTable::saveRegistry(ofstream& out) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* t = aircraftRegistry[i];
        while (t) {
            out << t->flightId << " " << t->model << " " << t->origin << " "
                << t->destination << " " << t->fuelLevel << endl;
            t = t->next;
        }
    }
}

void HashTable::loadEntry(string id, string model, string orig, string dest, int fuel) {
    registerAircraft(id, model, orig, dest, fuel);
}
void HashTable::updateFuelLevel(string flightId, int newFuel) {
    int index = hashFunction(flightId);
    HashNode* temp = aircraftRegistry[index];

    while (temp) {
        if (temp->flightId == flightId) {
            temp->fuelLevel = newFuel;
            cout << "\n> Fuel level updated for " << flightId << " to " << newFuel << "%\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Flight not found in Registry.\n";
}

void HashTable::updatePosition(string flightId, string newOrigin, string newDestination) {
    int index = hashFunction(flightId);
    HashNode* temp = aircraftRegistry[index];

    while (temp) {
        if (temp->flightId == flightId) {
            temp->origin = newOrigin;
            temp->destination = newDestination;
            cout << "\n> Route updated for " << flightId << ": " << newOrigin << " -> " << newDestination << "\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Flight not found in Registry.\n";
}

void HashTable::updateAircraft(string flightId, string model, string orig, string dest, int fuel) {
    int index = hashFunction(flightId);
    HashNode* temp = aircraftRegistry[index];

    while (temp) {
        if (temp->flightId == flightId) {
            temp->model = model;
            temp->origin = orig;
            temp->destination = dest;
            temp->fuelLevel = fuel;
            cout << "\n> Aircraft details updated for " << flightId << "\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Flight not found in Registry.\n";
}