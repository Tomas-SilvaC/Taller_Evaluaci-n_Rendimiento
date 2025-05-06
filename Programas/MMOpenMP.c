#include "MMOpenMP.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>
struct timeval inicio, fin; 
//Inicio de la muestra para la experimentación
void InicioMuestra(){
	//Utiliza la hora del dia
	gettimeofday(&inicio, (void *)0);
}

void FinMuestra(){
	//Finaliza el experimento o en otras palabras la instancia del mismo
	gettimeofday(&fin, (void *)0);
	fin.tv_usec -= inicio.tv_usec;
	fin.tv_sec  -= inicio.tv_sec;
	double tiempo = (double) (fin.tv_sec*1000000 + fin.tv_usec); 
	printf("%9.0f \n", tiempo);
}
//Impresión de la matriz
void impMatrix(size_t *matrix, int D){
	printf("\n");
	//Revisa si el tamaño es menor a 9
	if(D < 9){
		//Imprime por cada valor en la matriz el valor indicado uno por uno
		for(int i=0; i<D*D; i++){
			if(i%D==0) printf("\n");
			printf("%zu ", matrix[i]);
		}
		printf("\n**-----------------------------**\n");
	}
}

void iniMatrix(size_t *m1, size_t *m2, int D){
	//Inicializa la matriz
	for(int i=0; i<D*D; i++, m1++, m2++){
	//Se asigna, por el tamaño D * D que implica el tamaño de la matriz, los valores de cada elemento
		*m1 = i*2; // (size_t) rand()%10;	
		*m2 = i+2; // (size_t) rand()%10;	
	}
}
//Multiplicar las matrices
void multiMatrix(size_t *mA, size_t *mB, size_t *mC, int D){
	size_t Suma, *pA, *pB;
	//Utiliza OpenMP para realizar paralelismo a travez de multiplez procesadores o hilos
	#pragma omp parallel for private(pA, pB, Suma)

	//Realiza la multiplicación correspondiente de las dos matrices en una matriz resultado de igual tamaño
	for(int i=0; i<D; i++){
		for(int j=0; j<D; j++){
			pA = mA+i*D;	
			pB = mB+j; //pB = mB+(j*D);	
			Suma = 0;
			//Algoritmo filas por columnas
			for(int k=0; k<D; k++, pA++, pB+=D){
				Suma += *pA * *pB;
			}
			//Guarda el valor resultado donde corresponde
			mC[i*D+j] = Suma;
		}
	}
}