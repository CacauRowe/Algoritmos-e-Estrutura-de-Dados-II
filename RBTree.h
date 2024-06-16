#ifndef RBTREE_H
#define RBTREE_H

typedef enum { RED, BLACK } Color;

typedef struct RBNode {
    int key;
    struct RBNode* left, *right, *parent;
    Color color;
} RBNode;

void insertRB(RBNode** root, int key, int* rotations);
void deleteRB(RBNode** root, int key, int* rotations);
RBNode* findRB(RBNode* root, int key);

#endif // RBTREE_H
