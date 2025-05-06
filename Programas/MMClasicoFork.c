/*#######################################################################################
 #* Fecha: 20 sep 2025
 #* Autor: J.Corredor
 #* Documentado por: Tomas Silva, Juan Pabón Vargas, Felipe Rodriguez Amador, Arley Bernal, Sergio Pardo
 #* Tema: Programación Modular en C
 #* 	- Programa Multiplicación de Matrices algoritmo clásico
 #* 	- Paralelismo con fork
######################################################################################*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>
#include "MMFork.h"

int main(int argc, char *argv[]) {
    //En caso de que los argumentos no sean suficientes
	if (argc < 3) {
		printf("\n \t\tUse: $./nom_ejecutable Size Hilos \n");
		exit(0);
	}
	
	//Utiliza los parametros de entrada para el tamaño y numero de procesos a usar en fork
	int N      = (int) atoi(argv[1]);
	int num_P  = (int) atoi(argv[2]);
	//Se inician las matrices
    double *matA = (double *) calloc(N*N, sizeof(double));
    double *matB = (double *) calloc(N*N, sizeof(double));
    double *matC = (double *) calloc(N*N, sizeof(double));

    srand(time(0)); // Generación de numeros aleatoreos
    
    //Inicializa las matrices a multiplicar
    iniMatrix(matA, matB, N);
    //Imprime las matrices
    impMatrix(matA, N);
    impMatrix(matB, N);
    
    //Lineas por proceso
    int rows_per_process = N/ num_P;
    //Inicia la muestra
	InicioMuestra();
	//Para cada proceso del total
    for (int i = 0; i < num_P; i++) {
        pid_t pid = fork();
        
        if (pid == 0) { // para el proceso hijo
            int start_row = i * rows_per_process;
            int end_row = (i == num_P - 1) ? N : start_row + rows_per_process;
            
			multiMatrix(matA, matB, matC, N, start_row, end_row); 
            
			if(N<9){
            	// Imprimir la porcion ehca por el hijo
           		printf("\nChild PID %d calculated rows %d to %d:\n", getpid(), start_row, end_row-1);
           		//Impresión de algoritmo basico
            	for (int r = start_row; r < end_row; r++) {
                	for (int c = 0; c < N; c++) {
                    	printf(" %f ", matC[N*r+c]);
                	}
                	printf("\n");
            	}
			}
            exit(0); // Tras completar la tarea, el proceso hijo sigue existiendo
        } else if (pid < 0) { //En caso de fallo
            perror("fork failed");
            exit(1);
        }
    }
    
    // El proceso padre espera a que terminen sus hijos
    for (int i = 0; i < num_P; i++) {
        wait(NULL);
    }
  	
  	//Termina la muestra
	FinMuestra(); 
    //Liberar memoria
	free(matA);
	free(matB);
	free(matC);

    return 0;
}

