#include "MMPosix.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
//Variables 
pthread_mutex_t MM_mutex;

double *mA, *mB, *mC;

struct timeval inicio, fin;
//Inicia la muestra para el tiempo de ejecución
void InicioMuestra(){
	gettimeofday(&inicio, (void *)0);
}
//Finaliza la muestra del experimento
void FinMuestra(){
	gettimeofday(&fin, (void *)0);
	fin.tv_usec -= inicio.tv_usec;
	fin.tv_sec  -= inicio.tv_sec;
	double tiempo = (double) (fin.tv_sec*1000000 + fin.tv_usec);
	printf("%9.0f \n", tiempo);
}

//Inicializa las matrices para la multiplicación
void iniMatrix(int SZ){ 
	for(int i = 0; i < SZ*SZ; i++){
	    //Asigna valores aleatoreos a las matrices, salvo la resultado, la cual se inicia con 0
			mA[i] = rand() % 10; 
			mB[i] = rand() % 10;
			mC[i] = 0; 
		}	
}

//Impresión de matrices
void impMatrix(int sz, double *matriz){
	if(sz < 12){
    		for(int i = 0; i < sz*sz; i++){
     				if(i%sz==0) printf("\n");
            		printf(" %.3f ", matriz[i]);
			}	
    	printf("\n>-------------------->\n");
	}
}

//Algoritmo clasico de multiplicación de matrices
void *multiMatrix(void *variables){
    //Obtiene información de variables
	struct parametros *data = (struct parametros *)variables;
	
	//Información como el id del hilo, el numero de hilos y el inicio y fin del los mismos
	int idH = data->idH;
	int nH  = data->nH;
	int N   = data->N;
	int ini = (N/nH)*idH;
	int fin = (N/nH)*(idH+1);

    //Algoritmo clasico filas por columnas
    for (int i = ini; i < fin; i++){
        for (int j = 0; j < N; j++){
			double *pA, *pB, sumaTemp = 0.0;
			pA = mA + (i*N); 
			pB = mB + j;
            for (int k = 0; k < N; k++, pA++, pB+=N){
				sumaTemp += (*pA * *pB);
			}
			mC[i*N+j] = sumaTemp;
		}
	}

    //Finaliza el mutex
	pthread_mutex_lock (&MM_mutex);
	pthread_mutex_unlock (&MM_mutex);
	pthread_exit(NULL);
}


