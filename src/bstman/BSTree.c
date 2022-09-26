
#include "BSTree.h"

BSTree *bstreeCreate(FILE *input_file, int node_count) {
	int k;
	fscanf(input_file, "%d", &k);
	BSTree *tree = malloc(sizeof(BSTree));
	tree->key = k;
	tree->parent = NULL;
	tree->left_child = NULL;
	tree->right_child = NULL;
	tree->depth = 0;
	tree->is_leaf = true;

	for (int i = 1; i < node_count; i++) {
		fscanf(input_file, "%d", &k);
		bstreeInsert(tree, k);
	}

	return tree;
}

void bstreeInsert(BSTree *node, int value) {
	if (value < node->key) {
		if (node->left_child == NULL) {
			BSTree *new_node = malloc(sizeof(BSTree));
			new_node->key = value;
			new_node->parent = node;
			new_node->left_child = NULL;
			new_node->right_child = NULL;
			new_node->depth = node->depth + 1;
			new_node->is_leaf = true;
			node->left_child = new_node;
		}
		else {
			bstreeInsert(node->left_child, value);
		}
	}
	else if (value > node->key) {
		if (node->right_child == NULL) {
			BSTree *new_node = malloc(sizeof(BSTree));
			new_node->key = value;
			new_node->parent = node;
			new_node->left_child = NULL;
			new_node->right_child = NULL;
			new_node->depth = node->depth + 1;
			new_node->is_leaf = true;
			node->right_child = new_node;
		}
		else {
			bstreeInsert(node->right_child, value);
		}
	}
}

void bstreePrint(BSTree *tree) {
	if (tree == NULL) {
		return;
	}
	bstreePrint(tree->left_child);
	printf("%d ", tree->key);
	bstreePrint(tree->right_child);
}