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

void calculateStatistics(QuadTree *node, int *N, float *mu_arr, float *sigma_arr) {
	if (node->isLeaf) {
		int n = *N + 1;

		float mu_L = mu_arr[0];
		float mu_a = mu_arr[1];
		float mu_b = mu_arr[2];

		mu_arr[0] = mu_arr[0] + (node->L - mu_arr[0]) / (float)n;
		mu_arr[1] = mu_arr[1] + (node->a - mu_arr[1]) / (float)n;
		mu_arr[2] = mu_arr[2] + (node->b - mu_arr[2]) / (float)n;

		sigma_arr[0] = sigma_arr[0] + (node->L - mu_L) * (node->L - mu_arr[0]);
		sigma_arr[1] = sigma_arr[1] + (node->a - mu_a) * (node->a - mu_arr[1]);
		sigma_arr[2] = sigma_arr[2] + (node->b - mu_b) * (node->b - mu_arr[2]);

		*N = n;
	}
	else {
		calculateStatistics(node->UL, N, mu_arr, sigma_arr);
		calculateStatistics(node->UR, N, mu_arr, sigma_arr);
		calculateStatistics(node->LL, N, mu_arr, sigma_arr);
		calculateStatistics(node->LR, N, mu_arr, sigma_arr);
	}
}

void getStatistics(QuadTree *node, float *out_direction) {
	int *N = malloc(sizeof(int));
	*N = 0;

	float *mu_arr = malloc(3 * sizeof(float));
	mu_arr[0] = 0;
	mu_arr[1] = 0;
	mu_arr[2] = 0;

	float *sigma_arr = malloc(3 * sizeof(float));
	sigma_arr[0] = 0;
	sigma_arr[1] = 0;
	sigma_arr[2] = 0;

	calculateStatistics(node, N, mu_arr, sigma_arr);

	out_direction[0] = mu_arr[0];
	out_direction[1] = mu_arr[1];
	out_direction[2] = mu_arr[2];
	out_direction[3] = sqrt(sigma_arr[0] / (float)(*N));
	out_direction[4] = sqrt(sigma_arr[1] / (float)(*N));
	out_direction[5] = sqrt(sigma_arr[2] / (float)(*N));

	free(N);
	free(mu_arr);
	free(sigma_arr);
}