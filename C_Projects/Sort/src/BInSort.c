#include <stdlib.h>

typedef struct TN {
    int value;
    int count;
    struct TN* rightChild;
    struct TN* leftChild;
} TreeNode;

static TreeNode* MakeTree(int num) {
    TreeNode* tree = (TreeNode*) (malloc) (sizeof (TreeNode));
    tree->value = num;
    tree->count = 1;
    tree->rightChild = NULL;
    tree->leftChild = NULL;
    return tree;
}

static void FreeTree(TreeNode* n) {
    if (n->leftChild != NULL)
        FreeTree(n->leftChild);
    if (n->rightChild != NULL)
        FreeTree(n->rightChild);
    free(n);
}

static void SaveTree(TreeNode* n, int* sorted) {
	static int current = 0;
    if (n->leftChild != NULL)
        SaveTree(n->leftChild, sorted);
    int i;
    for (i = 0; i < n->count; ++i)
        sorted[current++] = n->value;
    if (n->rightChild != NULL)
        SaveTree(n->rightChild, sorted);
}

static void Insert(TreeNode* n, int num) {
	while (1) {
		if (num == n->value) {
			++n->count;
			return;
		} else if (num > n->value) {
			if (n->rightChild == NULL) {
				TreeNode* tree = MakeTree(num);
				n->rightChild = tree;
				return;
			}
			n = n->rightChild;
		} else if (num < n->value) {
			if (n->leftChild == NULL) {
				TreeNode* tree = MakeTree(num);
				n->leftChild = tree;
				return;
			}
			n = n->leftChild;
		}
	}
}

int* InsertionSortBinary(int* d, int n) {
    TreeNode* tree = MakeTree(d[0]);
    int i;
    for (i = 1; i < n; i++)
        Insert(tree, d[i]);
    SaveTree(tree, d);
    FreeTree(tree);
    return d;
}
