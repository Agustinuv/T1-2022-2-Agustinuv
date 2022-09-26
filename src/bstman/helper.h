// Las funciones utilizadas en este archivo y en helper.c fueron inspiradas o copiadas de:
// https://www.geeksforgeeks.org/avl-tree-set-1-insertion/

#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BSTree.h"

int max(int a, int b);

int height(BSTree *node);
