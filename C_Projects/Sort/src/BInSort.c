#include <stdlib.h>

static int current = 0;

struct TreeNode {
    int value;
    int count;
    struct TreeNode* rightChild;
    struct TreeNode* leftChild;
};

static struct TreeNode* MakeTree(int num) {
    struct TreeNode* tree = (struct TreeNode*) (malloc) (sizeof (struct TreeNode));
    tree->value = num;
    tree->count = 1;
    tree->rightChild = NULL;
    tree->leftChild = NULL;
    return tree;
}

static void FreeTree(struct TreeNode* n) {
    if (n->leftChild != NULL)
        FreeTree(n->leftChild);
    if (n->rightChild != NULL)
        FreeTree(n->rightChild);
    free(n);
}

static void SaveTree(struct TreeNode* n, int* sorted) {
    if (n->leftChild != NULL)
        SaveTree(n->leftChild, sorted);
    int i;
    for (i = 0; i < n->count; ++i)
        sorted[current++] = n->value;
    if (n->rightChild != NULL)
        SaveTree(n->rightChild, sorted);
}

static void Insert(struct TreeNode* n, int num) {
    if (num == n->value)
        ++n->count;
    else if (num > n->value) {
        if (n->rightChild == NULL) {
            struct TreeNode* tree = MakeTree(num);
            n->rightChild = tree;
            return;
        }
        Insert(n->rightChild, num);
    } else if (num < n->value) {
        if (n->leftChild == NULL) {
            struct TreeNode* tree = MakeTree(num);
            n->leftChild = tree;
            return;
        }
        Insert(n->leftChild, num);
    }
    return;
}

int* InsertionSortBinary(int* d, int n) {
    struct TreeNode* tree = MakeTree(d[0]);
    int i;
    for (i = 1; i < n; i++)
        Insert(tree, d[i]);
    current = 0;
    SaveTree(tree, d);
    FreeTree(tree);
    return d;
}
