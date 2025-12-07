#pragma once
#ifndef AVLTREE_H
#define AVLTREE_H

#include "Aircraft.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm> // for max

using namespace std;

struct LogNode {
    int timestamp;
    string flightId;
    string status;
    LogNode* left;
    LogNode* right;
    int height;
};

class AVLTree {
private:
    LogNode* root;

    int getHeight(LogNode* N);
    int getBalance(LogNode* N);
    LogNode* rightRotate(LogNode* y);
    LogNode* leftRotate(LogNode* x);
    LogNode* insertAVL(LogNode* node, int time, string id, string status);
    void inOrderTraversal(LogNode* root);
    void saveAVLRecursive(LogNode* root, ofstream& out);

public:
    AVLTree();
    void addLog(int time, string id, string status);
    void displayLogs();
    void saveLogs(ofstream& out);
};

#endif