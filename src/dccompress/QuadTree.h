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

// Imprimir la imagen a partir del QuadTree
void rePrintImg(QuadTree *node, Image *img);

// Copiar QuadTree en otro
QuadTree *copyQuadTree(QuadTree *node);

// Contador de hojas
int countLeaves(QuadTree *node);

// Liberar memoria del QuadTree
void freeQuadTree(QuadTree *node);