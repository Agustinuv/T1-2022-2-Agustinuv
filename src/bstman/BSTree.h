#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bstree_node {
	int key;

	struct bstree_node *parent;
	struct bstree_node *left_child;
	struct bstree_node *right_child;

	int depth;
	bool is_leaf;
} BSTree;

// Create a new BSTree
BSTree *bstreeCreate(FILE *input_file, int node_count);

// Insert a new node in the BSTree
void bstreeInsert(BSTree *node, int key);

// PATH search in the BSTree
void bstreePathSearch(BSTree *node, int key);

// Deep search in the BSTree
BSTree *findNode(BSTree *node, int key);

// Print the BSTree sorted
void bstreePrint(BSTree *node);

// Find subtree in tree
bool bstreeFindSubtree(BSTree *node, BSTree *subtree);

// Free the BSTree
void bstreeFree(BSTree *node);
