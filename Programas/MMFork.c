#include "MMFork.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>


struct timeval inicio, fin;
//Inicia la muestra usando la hora del dia
void InicioMuestra(){
	gettimeofday(&inicio, (void *)0);
}
//Finaliza la muestra con la impresión del tiempo de ejecución
void FinMuestra(){
	gettimeofday(&fin, (void *)0);
	fin.tv_usec -= inicio.tv_usec;
	fin.tv_sec  -= inicio.tv_sec;
	double tiempo = (double) (fin.tv_sec*1000000 + fin.tv_usec);
	printf("%9.0f \n", tiempo);
}
//Multiplica las matrices con el algoritmo clasico
void multiMatrix(double *mA, double *mB, double *mC, int D, int filaI, int filaF) {
	double Suma, *pA, *pB;
	//Algoritmo basico
    for (int i = filaI; i < filaF; i++) {
        for (int j = 0; j < D; j++) {
			Suma = 0;
			pA = mA+i*D;
			pB = mB+j;
            for (int k = 0; k < D; k++, pA++, pB+=D) {
				Suma += *pA * *pB;	
            }
			mC[i*D+j] = Suma;
        }
    }
}

//Impresión de matrices
void impMatrix(double *matrix, int D) {
    //Imprime solo si la matriz es mayor que 9 x 9
	if (D < 9) {
    	printf("\nImpresión	...\n");
    	//Imprime la matriz valor por valor
    	for (int i = 0; i < D*D; i++, matrix++) {
			if(i%D==0) printf("\n");
            	printf(" %f ", *matrix);
        	}
        printf("\n ");
    }
}

// Function to initialize matrix with random values
void iniMatrix(double *mA, double *mB, int D){
	for (int i = 0; i < D*D; i++, mA++, mB++){
            *mA = rand() % 10; 
            *mB = rand() % 10; 
        }
}
