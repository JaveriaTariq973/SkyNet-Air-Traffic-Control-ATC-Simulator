#include "AVLTree.h"

AVLTree::AVLTree() { root = nullptr; }

int AVLTree::getHeight(LogNode* N) { return (N == nullptr) ? 0 : N->height; }
int AVLTree::getBalance(LogNode* N) { return (N == nullptr) ? 0 : getHeight(N->left) - getHeight(N->right); }

LogNode* AVLTree::rightRotate(LogNode* y) {
    LogNode* x = y->left; LogNode* T2 = x->right;
    x->right = y; y->left = T2;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

LogNode* AVLTree::leftRotate(LogNode* x) {
    LogNode* y = x->right; LogNode* T2 = y->left;
    y->left = x; x->right = T2;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

LogNode* AVLTree::insertAVL(LogNode* node, int time, string id, string status) {
    if (node == nullptr) {
        LogNode* nn = new LogNode;
        nn->timestamp = time; nn->flightId = id; nn->status = status;
        nn->left = nn->right = nullptr; nn->height = 1;
        return nn;
    }
    if (time < node->timestamp) node->left = insertAVL(node->left, time, id, status);
    else node->right = insertAVL(node->right, time, id, status);

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int bal = getBalance(node);

    if (bal > 1 && time < node->left->timestamp) return rightRotate(node);
    if (bal < -1 && time > node->right->timestamp) return leftRotate(node);
    if (bal > 1 && time > node->left->timestamp) { node->left = leftRotate(node->left); return rightRotate(node); }
    if (bal < -1 && time < node->right->timestamp) { node->right = rightRotate(node->right); return leftRotate(node); }
    return node;
}

void AVLTree::inOrderTraversal(LogNode* root) {
    if (root) {
        inOrderTraversal(root->left);
        cout << "[" << root->timestamp << "] Flight " << root->flightId << ": " << root->status << endl;
        inOrderTraversal(root->right);
    }
}

void AVLTree::addLog(int time, string id, string status) {
    root = insertAVL(root, time, id, status);
}

void AVLTree::displayLogs() {
    cout << "\n=== DAILY FLIGHT LOG ===\n";
    if (!root) cout << "(Empty)\n";
    else inOrderTraversal(root);
}

void AVLTree::saveAVLRecursive(LogNode* root, ofstream& out) {
    if (root) {
        saveAVLRecursive(root->left, out);
        out << root->timestamp << " " << root->flightId << " " << root->status << endl;
        saveAVLRecursive(root->right, out);
    }
}

void AVLTree::saveLogs(ofstream& out) {
    saveAVLRecursive(root, out);
}