
#ifndef _MMFORK_H_
#define _MMFORK_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>

//inicio de muestra de tiempo
void InicioMuestra();

//Fin de muestra de tiempo
void FinMuestra();

//Multiplicar matrices
void multiMatrix(double *mA, double *mB, double *mC, int D, int filaI, int filaF);

//Imprimir matrices
void impMatrix(double *matrix, int D);

// Function to initialize matrix with random values
void iniMatrix(double *mA, double *mB, int D);

#endif