#include "QuadTree.h"

QuadTree *createQuadTree(QuadTree *parent, Image *img, int l, int r, int u, int d) {
	QuadTree *qt = malloc(sizeof(QuadTree));

	qt->parent = parent;
	qt->l = l;
	qt->r = r;
	qt->u = u;
	qt->d = d;
	qt->deep = parent ? parent->deep + 1 : 0;

	int deltaX = r - l;
	int deltaY = d - u;

	if (deltaX == 1 && deltaY == 1) {
		addLeaf(qt, img, l, u);
	}
	else if (deltaX != deltaY) {
		printf("Error: deltaX != deltaY\n");
		printf("deltaX: %d, deltaY: %d\n", deltaX, deltaY);
		exit(1);
	}
	else {
		int midX = (l + r) / 2;
		int midY = (u + d) / 2;

		qt->UL = createQuadTree(qt, img, l, midX, u, midY);
		qt->UR = createQuadTree(qt, img, midX, r, u, midY);
		qt->LL = createQuadTree(qt, img, l, midX, midY, d);
		qt->LR = createQuadTree(qt, img, midX, r, midY, d);

		qt->isLeaf = false;
	}

	return qt;
}

QuadTree *addLeaf(QuadTree *qt, Image *img, int x, int y) {
	qt->isLeaf = true;
	qt->UL = NULL;
	qt->UR = NULL;
	qt->LL = NULL;
	qt->LR = NULL;
	qt->L = img->pixels[y][x].L;
	qt->a = img->pixels[y][x].a;
	qt->b = img->pixels[y][x].b;

	return qt;
}

void rePrintImg(QuadTree *node, Image *img) {
	if (node->isLeaf) {
		for (int i = node->u; i < node->d; i++) {
			img_square_paint(
			    img,
			    node->u,
			    node->l,
			    node->r - node->l,
			    (Color){.L = node->L, .a = node->a, .b = node->b});
		}
	}
	else {
		rePrintImg(node->UL, img);
		rePrintImg(node->UR, img);
		rePrintImg(node->LL, img);
		rePrintImg(node->LR, img);
	}
}

int countLeaves(QuadTree *node) {
	if (node->isLeaf) {
		return 1;
	}
	else {
		return countLeaves(node->UL) + countLeaves(node->UR) +
		       countLeaves(node->LL) + countLeaves(node->LR);
	}
}