
#ifndef _MMOPENMP_H_
#define _MMOPENMP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>


//Inicio de la muestra para la experimentación
void InicioMuestra();
void FinMuestra();
//Impresión de la matriz
void impMatrix(size_t *matrix, int D);
//Inicializa la matriz
void iniMatrix(size_t *m1, size_t *m2, int D);
//Multiplicar las matrices
void multiMatrix(size_t *mA, size_t *mB, size_t *mC, int D);

#endif