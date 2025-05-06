/*#######################################################################################
 #* Fecha: 20 sep 2025
 #* Autor: J.Corredor
 #* Documentado por: Tomas Silva, Juan Pabón Vargas, Felipe Rodriguez Amador, Arley Bernal, Sergio Pardo
 #* Tema: Programación Modular en C
 #* 	- Programa Multiplicación de Matrices algoritmo clásico
 #* 	- Paralelismo con OpenMP
######################################################################################*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>
#include "MMOpenMP.h"


int main(int argc, char *argv[]){
	//Revision de cantidad de elementos
	if(argc < 3){
		printf("\n Use: $./clasicaOpenMP SIZE Hilos \n\n");
		exit(0);
	}

	//Primero el tamaño de la matriz
	int N = atoi(argv[1]);
	//Numero de hilos
	int TH = atoi(argv[2]);
	//Se inicializan las matrices A, B y C que se usaran para los datos
	size_t *matrixA  = (size_t *)calloc(N*N, sizeof(size_t));
	size_t *matrixB  = (size_t *)calloc(N*N, sizeof(size_t));
	size_t *matrixC  = (size_t *)calloc(N*N, sizeof(size_t));
	
	if (!matrixA || !matrixB || !matrixC) {
		fprintf(stderr, "Error: No se pudo asignar memoria. Reduce el tamaño de la matriz (N=%d).\n", N);
		free(matrixA); free(matrixB); free(matrixC);
		return EXIT_FAILURE;
	}
	//Rand para el llenado de datos
	srand(time(NULL));
	//Se define el numero de hilos de OpenMP
	omp_set_num_threads(TH);
	//Inicializa las matrices con su respectivo tamaño
	iniMatrix(matrixA, matrixB, N);
	//Muestra matrices creadas
	impMatrix(matrixA, N);
	impMatrix(matrixB, N);
	//Se hace la instancia del experimento para la multiplicación de matrices
	InicioMuestra();
	multiMatrix(matrixA, matrixB, matrixC, N);
	FinMuestra();
	//Imprime matriz resultado
	impMatrix(matrixC, N);

	/*Liberación de Memoria*/
	free(matrixA);
	free(matrixB);
	free(matrixC);
	
	return 0;
}

