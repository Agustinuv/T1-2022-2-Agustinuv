#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BSTree.h"

/* Retorna true si ambos strings son iguales */
bool string_equals(char* string1, char* string2) {
	return !strcmp(string1, string2);
}

/* Revisa que los parametros del programa sean válidos */
bool check_arguments(int argc, char** argv) {
	if (argc != 3) {
		printf("Modo de uso: %s INPUT OUTPUT\n", argv[0]);
		printf("Donde:\n");
		printf("\tINPUT es la ruta del archivo de input\n");
		printf("\tOUTPUT es la ruta del archivo de output\n");
		exit(1);
	}

	return true;
}

int main(int argc, char** argv) {
	check_arguments(argc, argv);

	FILE* input_file = fopen(argv[1], "r");
	FILE* output_file = fopen(argv[2], "w");

	int node_count;
	int query_count;

	fscanf(input_file, "%d", &node_count);

	BSTree* tree = bstreeCreate(input_file, node_count);

	fscanf(input_file, "%d", &query_count);
	/* leemos las consultas */
	char command[32];
	int value;
	BSTree* result;
	for (int i = 0; i < query_count; i++) {
		fscanf(input_file, "%s %d", command, &value);
		// fprintf(output_file, "--------------------\n");

		if (string_equals(command, "PATH")) {
			printf("PATH %d\n", value);
			bstreePathSearch(tree, value, output_file);
		}
		else if (string_equals(command, "DEEP")) {
			printf("DEEP %d\n", value);
			result = findNode(tree, value);
			fprintf(output_file, "%d\n", result->depth);
			// printf("Result: %d\n", result->depth);
		}
		else if (string_equals(command, "ORDER")) {
			printf("ORDER\n");
			bstreePrint(tree, output_file);
			fprintf(output_file, "\n");
			// printf("\n");
		}

		else {
			printf("Comando desconocido: %s\n", command);
		}
	}

	bstreeFree(tree);

	fclose(input_file);
	fclose(output_file);
	return 0;
}
