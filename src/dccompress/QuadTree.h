#pragma once

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../imagelib/imagelib.h"

typedef struct quadtree {
	struct quadtree *parent;
	struct quadtree *UL;   // Upper Left
	struct quadtree *UR;   // Upper Right
	struct quadtree *LL;   // Lower Left
	struct quadtree *LR;   // Lower Right
	int l, r, u, d;        // left, right, up, down limits

	float L;   // luminosidad 0 a 100
	float a;   // verde-magenta -128 a 128
	float b;   // azul-amarillo -128 a 128

	int deep;   // profundidad del nodo
	bool isLeaf;
} QuadTree;

// A partir de la información, crear el QuadTree y devolverlo
QuadTree *createQuadTree(QuadTree *parent, Image *img, int l, int r, int u, int d);

// En caso de ser una hoja
QuadTree *addLeaf(QuadTree *qt, Image *img, int x, int y);

// Calculos de la media y la desviación estandar del cuadrante
void getStatistics(QuadTree *node, float *out_direction);

// Calcula la media y la desviación estandar de un cuadrante
void calculateStatistics(QuadTree *node, int *N, float *mu_arr, float *sigma_arr);
