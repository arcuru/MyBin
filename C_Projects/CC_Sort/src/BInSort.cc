#include <stdlib.h>

static int current = 0;

struct TreeNode {
	int value;
	int count;
	TreeNode* rightChild;
	TreeNode* leftChild;
};

static TreeNode* MakeTree(int num) {
	TreeNode* tree;
	tree = (TreeNode*) (malloc)(sizeof(TreeNode));
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
	if (n->leftChild != NULL)
		SaveTree(n->leftChild, sorted);
	for (int i = 0; i < n->count; ++i)
		sorted[current++] = n->value;
	if (n->rightChild != NULL)
		SaveTree(n->rightChild, sorted);
}

static void Insert(TreeNode* n, int num) {
	if (num == n->value)
		n->count++;
	else if (num > n->value) {
		if (n->rightChild == NULL) {
			TreeNode* tree = MakeTree(num);
			n->rightChild = tree;
			return;
		}
		Insert(n->rightChild, num);
	}
	else if (num < n->value) {
		if (n->leftChild == NULL) {
			TreeNode* tree = MakeTree(num);
			n->leftChild = tree;
			return;
		}
		Insert(n->leftChild, num);
	}
	return;
}

int* InsertionSortBinary(int* d, int n) {
	TreeNode* tree = MakeTree(d[0]);
	for (int i = 1; i < n; i++)
		Insert(tree, d[i]);
	current = 0;
	SaveTree(tree, d);
	FreeTree(tree);
	return d;
}
