#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "AVLTree.h"
#include "RBTree.h"

#define N 10000
#define M 1000

void runTest() {
    AVLNode* avlRoot = NULL;
    RBNode* rbRoot = NULL;
    int avlRotations = 0, rbRotations = 0;
    int values[N], randomValues[M];

    for (int i = 0; i < N; i++) values[i] = i;
    for (int i = 0; i < M; i++) randomValues[i] = rand() % N;

    clock_t start, end;

    // Inserção
    start = clock();
    for (int i = 0; i < N; i++) avlRoot = insertAVL(avlRoot, values[i], &avlRotations);
    end = clock();
    double avlInsertTime = ((double) (end - start)) / CLOCKS_PER_SEC;

    start = clock();
    for (int i = 0; i < N; i++) insertRB(&rbRoot, values[i], &rbRotations);
    end = clock();
    double rbInsertTime = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Inserção AVL: Tempo = %.5f s, Rotações = %d\n", avlInsertTime, avlRotations);
    printf("Inserção Rubro-Negra: Tempo = %.5f s, Rotações = %d\n", rbInsertTime, rbRotations);

    avlRotations = rbRotations = 0;

    // Remoção
    start = clock();
    for (int i = 0; i < N; i++) avlRoot = deleteAVL(avlRoot, values[i], &avlRotations);
    end = clock();
    double avlDeleteTime = ((double) (end - start)) / CLOCKS_PER_SEC;

    start = clock();
    for (int i = 0; i < N; i++) deleteRB(&rbRoot, values[i], &rbRotations);
    end = clock();
    double rbDeleteTime = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Remoção AVL: Tempo = %.5f s, Rotações = %d\n", avlDeleteTime, avlRotations);
    printf("Remoção Rubro-Negra: Tempo = %.5f s, Rotações = %d\n", rbDeleteTime, rbRotations);

    // Busca
    start = clock();
    for (int i = 0; i < M; i++) findAVL(avlRoot, randomValues[i]);
    end = clock();
    double avlFindTime = ((double) (end - start)) / CLOCKS_PER_SEC;

    start = clock();
    for (int i = 0; i < M; i++) findRB(rbRoot, randomValues[i]);
    end = clock();
    double rbFindTime = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Busca AVL: Tempo = %.5f s\n", avlFindTime);
    printf("Busca Rubro-Negra: Tempo = %.5f s\n", rbFindTime);
}

int main() {
    srand(time(0));
    runTest();
    return 0;
}
