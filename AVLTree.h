#ifndef AVLTREE_H
#define AVLTREE_H

typedef struct AVLNode {
    int key;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;

AVLNode* insertAVL(AVLNode* node, int key, int* rotations);
AVLNode* deleteAVL(AVLNode* root, int key, int* rotations);
AVLNode* findAVL(AVLNode* root, int key);

#endif // AVLTREE_H
