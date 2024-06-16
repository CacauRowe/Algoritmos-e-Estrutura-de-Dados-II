#include "RBTree.h"
#include <stdlib.h>

// Funções auxiliares (ex. createRBNode, minValueNodeRB, etc.) aqui
// (mantém as definições auxiliares)

static RBNode* createRBNode(int key) {
    RBNode* node = (RBNode*)malloc(sizeof(RBNode));
    node->key = key;
    node->left = node->right = node->parent = NULL;
    node->color = RED;
    return node;
}

static RBNode* minValueNodeRB(RBNode* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

static void leftRotateRB(RBNode** root, RBNode* x, int* rotations) {
    RBNode* y = x->right;
    x->right = y->left;
    if (y->left != NULL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL) *root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
    (*rotations)++;
}

static void rightRotateRB(RBNode** root, RBNode* y, int* rotations) {
    RBNode* x = y->left;
    y->left = x->right;
    if (x->right != NULL) x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NULL) *root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;
    x->right = y;
    y->parent = x;
    (*rotations)++;
}

// Fixup após a inserção
static void insertFixUpRB(RBNode** root, RBNode* z, int* rotations) {
    while (z != *root && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBNode* y = z->parent->parent->right;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotateRB(root, z, rotations);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotateRB(root, z->parent->parent, rotations);
            }
        } else {
            RBNode* y = z->parent->parent->left;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotateRB(root, z, rotations);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotateRB(root, z->parent->parent, rotations);
            }
        }
    }
    (*root)->color = BLACK;
}

// Funções de inserção, remoção e busca para árvore Rubro-Negra

void insertRB(RBNode** root, int key, int* rotations) {
    RBNode* z = createRBNode(key);
    RBNode* y = NULL;
    RBNode* x = *root;

    while (x != NULL) {
        y = x;
        if (z->key < x->key) x = x->left;
        else x = x->right;
    }
    z->parent = y;
    if (y == NULL) *root = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;

    insertFixUpRB(root, z, rotations);
}

// Fixup após a remoção
static void deleteFixUpRB(RBNode** root, RBNode* x, int* rotations) {
    while (x != *root && (x == NULL || x->color == BLACK)) {
        if (x == x->parent->left) {
            RBNode* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotateRB(root, x->parent, rotations);
                w = x->parent->right;
            }
            if ((w->left == NULL || w->left->color == BLACK) &&
                (w->right == NULL || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right == NULL || w->right->color == BLACK) {
                    if (w->left != NULL) w->left->color = BLACK;
                    w->color = RED;
                    rightRotateRB(root, w, rotations);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->right != NULL) w->right->color = BLACK;
                leftRotateRB(root, x->parent, rotations);
                x = *root;
            }
        } else {
            RBNode* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotateRB(root, x->parent, rotations);
                w = x->parent->left;
            }
            if ((w->right == NULL || w->right->color == BLACK) &&
                (w->left == NULL || w->left->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left == NULL || w->left->color == BLACK) {
                    if (w->right != NULL) w->right->color = BLACK;
                    w->color = RED;
                    leftRotateRB(root, w, rotations);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->left != NULL) w->left->color = BLACK;
                rightRotateRB(root, x->parent, rotations);
                x = *root;
            }
        }
    }
    if (x != NULL) x->color = BLACK;
}

void deleteRB(RBNode** root, int key, int* rotations) {
    RBNode* z = *root;
    RBNode* y, *x;

    while (z != NULL && z->key != key) {
        if (key < z->key) z = z->left;
        else z = z->right;
    }

    if (z == NULL) return;

    y = z;
    Color yOriginalColor = y->color;

    if (z->left == NULL) {
        x = z->right;
        if (z->parent == NULL) *root = x;
        else if (z == z->parent->left) z->parent->left = x;
        else z->parent->right = x;
        if (x != NULL) x->parent = z->parent;
    } else if (z->right == NULL) {
        x = z->left;
        if (z->parent == NULL) *root = x;
        else if (z == z->parent->left) z->parent->left = x;
        else z->parent->right = x;
        if (x != NULL) x->parent = z->parent;
    } else {
        y = minValueNodeRB(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x != NULL) x->parent = y;
        } else {
            if (y->parent != NULL) {
                if (x != NULL) x->parent = y->parent;
                y->parent->left = x;
            }
            y->right = z->right;
            if (z->right != NULL) z->right->parent = y;
        }
        if (z->parent == NULL) *root = y;
        else if (z == z->parent->left) z->parent->left = y;
        else z->parent->right = y;
        y->parent = z->parent;
        y->color = z->color;
        y->left = z->left;
        if (z->left != NULL) z->left->parent = y;
    }
    free(z);
    if (yOriginalColor == BLACK)
        deleteFixUpRB(root, x, rotations);
}

RBNode* findRB(RBNode* root, int key) {
    if (root == NULL || root->key == key)
        return root;
    if (key < root->key)
        return findRB(root->left, key);
    return findRB(root->right, key);
}
