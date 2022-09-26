
#include "filters.h"

void filterAlpha(QuadTree *node, float alpha, float *mu_arr, float *sigma_arr) {
	if (!node->isLeaf) {
		mu_arr[0] = 0;
		mu_arr[1] = 0;
		mu_arr[2] = 0;

		sigma_arr[0] = 0;
		sigma_arr[1] = 0;
		sigma_arr[2] = 0;

		// get statistics
		getStatistics(node, mu_arr, sigma_arr);

		float sigma = (sigma_arr[0] + sigma_arr[1] + sigma_arr[2]) / 3;

		if (sigma <= alpha) {
			printf("Filtrando cuadrante de anchos %d con sigma %f\n", node->r - node->l, sigma);

			node->isLeaf = true;
			node->UL = NULL;
			node->UR = NULL;
			node->LL = NULL;
			node->LR = NULL;
			node->L = mu_arr[0];
			node->a = mu_arr[1];
			node->b = mu_arr[2];
		}
		else {
			filterAlpha(node->UL, alpha, mu_arr, sigma_arr);
			filterAlpha(node->UR, alpha, mu_arr, sigma_arr);
			filterAlpha(node->LL, alpha, mu_arr, sigma_arr);
			filterAlpha(node->LR, alpha, mu_arr, sigma_arr);
		}
	}
}

void useFilterAlpha(QuadTree *node, float alpha) {
	float *mu_arr = malloc(3 * sizeof(float));
	float *sigma_arr = malloc(3 * sizeof(float));

	filterAlpha(node, alpha, mu_arr, sigma_arr);

	free(mu_arr);
	free(sigma_arr);
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

void getStatistics(QuadTree *node, float *mu_arr, float *sigma_arr) {
	int *N = malloc(sizeof(int));
	*N = 0;

	calculateStatistics(node, N, mu_arr, sigma_arr);

	sigma_arr[0] = sqrt(sigma_arr[0] / (float)(*N));
	sigma_arr[1] = sqrt(sigma_arr[1] / (float)(*N));
	sigma_arr[2] = sqrt(sigma_arr[2] / (float)(*N));

	free(N);
}
