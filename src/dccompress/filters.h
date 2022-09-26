#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "QuadTree.h"

// Filtro alfa
void filterAlpha(QuadTree *node, float alpha, float *mu_arr, float *sigma_arr);

// Function that calls filterAlpha
void useFilterAlpha(QuadTree *node, float alpha);

// Compresión de la imagen
int compressImage(QuadTree *tree, int h, int limit_inf, int limit_sup);

// Llamada a la función de compresión
void useCompressImage(QuadTree *tree, int h);

// Calculos de la media y la desviación estandar del cuadrante
void getStatistics(QuadTree *node, float *mu_arr, float *sigma_arr);

// Calcula la media y la desviación estandar de un cuadrante
void calculateStatistics(QuadTree *node, int *N, float *mu_arr, float *sigma_arr);
