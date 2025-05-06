#!/usr/bin/perl
#**************************************************************
#         		Pontificia Universidad Javeriana
#     Autor: J. Corredor
#     Documentado por: Tomas Silva, Juan Pabón Vargas, Felipe Rodriguez Amador, Arley Bernal, Sergio Pardo
#     Fecha: Mayo 2025
#     Materia: Sistemas Operativos
#     Tema: Taller de Evaluación de Rendimiento
#     Fichero: script automatización ejecución por lotes 
#****************************************************************/
use File::Path qw(make_path);

$Path = `pwd`;
chomp($Path);

# Define los ejecutables y versiones disponibles
%Ejecutables = (
    'Posix'   => 'MMPosix',
    'Fork'    => 'MMFork',
    'OpenMP'  => 'MMOpenMP'
);
# Define los tamaños de las matrices
@Size_Matriz = (50, 100, 300);
# Define la cantidad de hilos
@Num_Hilos   = (1, 2, 4);
# Y finalmente define el numero de repeticiones de ejecución
$Repeticiones = 30;

foreach $version (keys %Ejecutables) {
    my $dir = "$Path/resultados_$version";
    make_path($dir);

    foreach $size (@Size_Matriz){
        foreach $hilo (@Num_Hilos) {
            if ($version eq 'Fork') {
                # Da el nombre "Procesos-$hilo" a los hilos creados
                $hilo_label = "Procesos-$hilo";
                # Crea archivos de resultados ejecución .dat
                $nombre_salida = "$dir/$Ejecutables{$version}-$size-$hilo_label.dat";
                #Guardado de elementos
                for ($i=0; $i<$Repeticiones; $i++) {
                    system("$Path/$Ejecutables{$version} $size $hilo >> $nombre_salida");
                }
            }if ($version eq 'OpenMP') {
                $hilo_label = "Hilos-$hilo";
                # Crea archivos de resultados ejecución .dat
                $nombre_salida = "$dir/$Ejecutables{$version}-$size-$size-$hilo_label.dat";
                #Guardado de elementos
                for ($i=0; $i<$Repeticiones; $i++) {
                    system("$Path/$Ejecutables{$version} $size $size $hilo >> $nombre_salida");
                }
            }else {
                $hilo_label = "Hilos-$hilo";
                # Crea archivos de resultados ejecución .dat
                $nombre_salida = "$dir/$Ejecutables{$version}-$size-$hilo_label.dat";
                #Guardado de elementos
                for ($i=0; $i<$Repeticiones; $i++) {
                    system("$Path/$Ejecutables{$version} $size $hilo >> $nombre_salida");
                }
                #Se evitan impresiones para preservar la limpieza del experimento
            }
        }
    }
}
