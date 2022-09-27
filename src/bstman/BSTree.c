
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

void bstreePrint(BSTree *tree, FILE *output_file) {
	if (tree == NULL) {
		return;
	}
	bstreePrint(tree->left_child, output_file);
	fprintf(output_file, "%d ", tree->key);
	// printf("%d ", tree->key);
	bstreePrint(tree->right_child, output_file);
}

void bstreeFree(BSTree *tree) {
	if (tree == NULL) {
		return;
	}
	bstreeFree(tree->left_child);
	bstreeFree(tree->right_child);
	free(tree);
}

BSTree *findNode(BSTree *node, int key) {
	if (node == NULL) {
		return NULL;
	}
	else if (node->key == key) {
		return node;
	}
	else if (key < node->key) {
		return findNode(node->left_child, key);
	}
	else {
		return findNode(node->right_child, key);
	}
}

void bstreePathSearch(BSTree *node, int key, FILE *output_file) {
	if (node == NULL) {
		fprintf(output_file, "X \n");
		// printf("X \n");
	}
	else if (node->key == key) {
		fprintf(output_file, "%d \n", node->key);
		// printf("%d \n", node->key);
	}
	else if (key < node->key) {
		fprintf(output_file, "%d ", node->key);
		// printf("%d ", node->key);
		bstreePathSearch(node->left_child, key, output_file);
	}
	else {
		fprintf(output_file, "%d ", node->key);
		// printf("%d ", node->key);
		bstreePathSearch(node->right_child, key, output_file);
	}
}

bool compareTrees(BSTree tree1, BSTree treee2) {
	printf("tree1: %d, tree2: %d\n", tree1.key, treee2.key);
	if (tree1.key != treee2.key) {
		return false;
	}
	if (tree1.left_child == NULL && treee2.left_child != NULL) {
		return false;
	}
	if (tree1.left_child != NULL && treee2.left_child == NULL) {
		return false;
	}
	if (tree1.right_child == NULL && treee2.right_child != NULL) {
		return false;
	}
	if (tree1.right_child != NULL && treee2.right_child == NULL) {
		return false;
	}
	if (tree1.left_child != NULL && treee2.left_child != NULL) {
		if (!compareTrees(*tree1.left_child, *treee2.left_child)) {
			return false;
		}
	}
	if (tree1.right_child != NULL && treee2.right_child != NULL) {
		if (!compareTrees(*tree1.right_child, *treee2.right_child)) {
			return false;
		}
	}
	return true;
}

int isSubtree(BSTree *tree, BSTree *subtree) {
	if (tree == NULL) {
		return 0;
	}

	BSTree *start_subtree_node = findNode(tree, subtree->key);

	if (start_subtree_node == NULL) {
		return 0;
	}

	if (compareTrees(*start_subtree_node, *subtree)) {
		return 1;
	}

	return 0;
}