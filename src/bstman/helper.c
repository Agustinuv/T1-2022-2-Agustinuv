
#include "helper.h"

int max(int a, int b) {
	return (a > b) ? a : b;
}

int height(BSTree *node) {
	if (node->is_leaf)
		return 1;
	return 1 + max(height(node->left_child), height(node->right_child));
}
