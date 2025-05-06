# Taller de evaluación de rendimiento
Integrantes: Tomas Alejandro Silva Correal, Juan Pabon Vargas, Sergio Pardo Hurtado, Juan Felipe Rodriguez Amador y Arley Bernal
El objetivo de este taller es comparar la ejecución de un algoritmo en serie y en paralelo. Este se realizo en diferentes sistemas de cómputo y se comparo los resultados para poder llegar a una conclusión y poder dar recomendaciones sobre las diferentes formas de ejecutar un algoritmo.

# Para su respectiva ejecución
Generar archivos ejecutables mediante el makefile integrado o usando el comando gcc programas_a_compilar_incluyendo_librerias.c -o nombre_ejecutable
(Cabe mencionar que la creación del ejecutable de OpenMP necesita la linea "-fopenmp" al final del comando)
Es necesario asegurarse que los ejecutables tengan el mismo nombre a los propuestos en el archivo "lanza.pl" siendo estos los siguientes:
  - OpenMP: MMOpenMP
  - Fork: MMFork
  - Posix: MMPosix
Tras tener los ejecutables ejecutar el programa "lanza.pl", el cual se encargara de generar las ejecuciónes y guardar los datos correspondientes
