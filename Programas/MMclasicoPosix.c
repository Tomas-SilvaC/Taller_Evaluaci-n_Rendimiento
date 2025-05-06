/*#######################################################################################
 #* Fecha: 20 sep 2025
 #* Autor: J.Corredor
 #* Documentado por: Tomas Silva, Juan Pabón Vargas, Felipe Rodriguez Amador, Arley Bernal, Sergio Pardo
 #* Tema: Programación Modular en C
 #* 	- Programa Multiplicación de Matrices algoritmo clásico
 #* 	- Paralelismo con posix
######################################################################################*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "MMPosix.h"
double MEM_CHUNK[DATA_SIZE];

int main(int argc, char *argv[]){
    //Revisa la cantidad de argumentos
	if (argc < 3){
		printf("Ingreso de argumentos \n $./ejecutable tamMatriz numHilos\n");
		exit(0);	
	}
	
	//Tamaño de las matrices
    int SZ = atoi(argv[1]); 
    //Numero de hilos a crear
    int n_threads = atoi(argv[2]); 
    
    //define hilos de proceso
    pthread_t p[n_threads];
    pthread_attr_t atrMM;
    
    //Crea las matrices con tamaño SZ
	mA = MEM_CHUNK;
	mB = mA + SZ*SZ;
	mC = mB + SZ*SZ;

    //Inicializa las matrices
	iniMatrix(SZ);
	//Imprime matrices
	impMatrix(SZ, mA);
	impMatrix(SZ, mB);
    //Inicio de muestra de experimento
	InicioMuestra();
    
  
	pthread_mutex_init(&MM_mutex, NULL);
	pthread_attr_init(&atrMM);
	pthread_attr_setdetachstate(&atrMM, PTHREAD_CREATE_JOINABLE);

    //Crea hilos y asigna parametos identificadores a un struct con datos
    for (int j=0; j<n_threads; j++){
		struct parametros *datos = (struct parametros *) malloc(sizeof(struct parametros)); 
		datos->idH = j;
		datos->nH  = n_threads;
		datos->N   = SZ;
		//Hilos con el objetivo de multiplicar las matrices
        pthread_create(&p[j],&atrMM,multiMatrix,(void *)datos);
	}
    //Evita condición de carrera mediante join
    for (int j=0; j<n_threads; j++)
        pthread_join(p[j],NULL);
    //Finaliza la muestra del experimento
	FinMuestra();
	//Imprime el resultado de la matriz resultado
	impMatrix(SZ, mC);
    //Termina los hilos y acaba el programa
	pthread_attr_destroy(&atrMM);
	pthread_mutex_destroy(&MM_mutex);
	pthread_exit (NULL);
}

