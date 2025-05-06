#ifndef _MMPOSIX_H_
#define _MMPOSIX_H_

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define DATA_SIZE (1024*1024*64*3) 

//Struct que contiene parametros de los hilos
struct parametros{
	int nH;
	int idH;
	int N;
};
//Mutex iniciado junto a matrices y el tamaño de los datos o chunk de memoria
extern pthread_mutex_t MM_mutex;
extern double MEM_CHUNK[DATA_SIZE];

extern double *mA, *mB, *mC;

extern struct timeval inicio, fin;

//Inicia la muestra del experimento
void InicioMuestra();
//Finaliza la muestra del experimento
void FinMuestra();
//Inicializa las matrices del procedimiento
void iniMatrix(int SZ);
//Impresión de una matriz
void impMatrix(int sz, double *matriz);
//Algoritmo basico de multiplicación de matrices
void *multiMatrix(void *variables);

#endif
