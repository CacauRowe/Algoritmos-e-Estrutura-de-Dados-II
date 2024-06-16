#include "AVLTree.h"
#include <stdlib.h>

// Funções auxiliares (ex. createAVLNode, max, height) aqui
// (mantém as definições auxiliares)

static AVLNode* createAVLNode(int key) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

static int height(AVLNode* node) {
    return node ? node->height : 0;
}

static int max(int a, int b) {
    return (a > b) ? a : b;
}

// Rotação à direita
static AVLNode* rightRotateAVL(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

// Rotação à esquerda
static AVLNode* leftRotateAVL(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

// Função para obter o fator de balanceamento do nó
static int getBalance(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Funções de inserção, remoção e busca para AVL

AVLNode* insertAVL(AVLNode* node, int key, int* rotations) {
    if (node == NULL) return createAVLNode(key);
    if (key < node->key)
        node->left = insertAVL(node->left, key, rotations);
    else if (key > node->key)
        node->right = insertAVL(node->right, key, rotations);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key) {
        (*rotations)++;
        return rightRotateAVL(node);
    }
    if (balance < -1 && key > node->right->key) {
        (*rotations)++;
        return leftRotateAVL(node);
    }
    if (balance > 1 && key > node->left->key) {
        (*rotations)++;
        node->left = leftRotateAVL(node->left);
        return rightRotateAVL(node);
    }
    if (balance < -1 && key < node->right->key) {
        (*rotations)++;
        node->right = rightRotateAVL(node->right);
        return leftRotateAVL(node);
    }
    return node;
}

AVLNode* minValueNodeAVL(AVLNode* node) {
    AVLNode* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

AVLNode* deleteAVL(AVLNode* root, int key, int* rotations) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteAVL(root->left, key, rotations);
    else if (key > root->key)
        root->right = deleteAVL(root->right, key, rotations);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            AVLNode* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            AVLNode* temp = minValueNodeAVL(root->right);
            root->key = temp->key;
            root->right = deleteAVL(root->right, temp->key, rotations);
        }
    }
    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) {
        (*rotations)++;
        return rightRotateAVL(root);
    }
    if (balance > 1 && getBalance(root->left) < 0) {
        (*rotations)++;
        root->left = leftRotateAVL(root->left);
        return rightRotateAVL(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) {
        (*rotations)++;
        return leftRotateAVL(root);
    }
    if (balance < -1 && getBalance(root->right) > 0) {
        (*rotations)++;
        root->right = rightRotateAVL(root->right);
        return leftRotateAVL(root);
    }
    return root;
}

AVLNode* findAVL(AVLNode* root, int key) {
    if (root == NULL || root->key == key)
        return root;
    if (key < root->key)
        return findAVL(root->left, key);
    return findAVL(root->right, key);
}
