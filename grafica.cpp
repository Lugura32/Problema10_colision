#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include "../funcion/Grafica.h"

using namespace std;

void generarGraficas() {
    // Script para GNUplot - Posición vs Tiempo
    string script_posicion = R"(
set terminal png size 1000,600 enhanced font "Arial,12"
set output 'posicion_vs_tiempo.png'
set title 'Posicion vs Tiempo'
set xlabel 'Tiempo (s)'
set ylabel 'Posicion (m)'
set grid
set key top left
plot 'simulacion.txt' using 1:2 with lines lw 2 title 'Posicion x(t)'
)";

    // Script para GNUplot - Velocidad vs Tiempo
    string script_velocidad = R"(
set terminal png size 1000,600 enhanced font "Arial,12"
set output 'velocidad_vs_tiempo.png'
set title 'Velocidad vs Tiempo'
set xlabel 'Tiempo (s)'
set ylabel 'Velocidad (m/s)'
set grid
set key top left
plot 'simulacion.txt' using 1:3 with lines lw 2 lc rgb "red" title 'Velocidad v(t)'
)";

    // Script para GNUplot - Energía Cinética vs Tiempo
    string script_energia = R"(
set terminal png size 1000,600 enhanced font "Arial,12"
set output 'energia_vs_tiempo.png'
set title 'Energia Cinetica vs Tiempo'
set xlabel 'Tiempo (s)'
set ylabel 'Energia Cinetica (J)'
set grid
set key top left
plot 'simulacion.txt' using 1:4 with lines lw 2 lc rgb "green" title 'Energia Cinetica'
)";

    // Guardar scripts en archivos temporales
    ofstream file1("script_posicion.gnu");
    if (file1.is_open()) {
        file1 << script_posicion;
        file1.close();
    } else {
        cerr << "Error: No se pudo crear script_posicion.gnu" << endl;
        return;
    }

    ofstream file2("script_velocidad.gnu");
    if (file2.is_open()) {
        file2 << script_velocidad;
        file2.close();
    } else {
        cerr << "Error: No se pudo crear script_velocidad.gnu" << endl;
        return;
    }

    ofstream file3("script_energia.gnu");
    if (file3.is_open()) {
        file3 << script_energia;
        file3.close();
    } else {
        cerr << "Error: No se pudo crear script_energia.gnu" << endl;
        return;
    }

    // Ejecutar GNUplot para generar las gráficas
    cout << "Generando graficas..." << endl;
    
    int result1 = system("gnuplot script_posicion.gnu");
    int result2 = system("gnuplot script_velocidad.gnu");
    int result3 = system("gnuplot script_energia.gnu");

    // Limpiar archivos temporales
    remove("script_posicion.gnu");
    remove("script_velocidad.gnu");
    remove("script_energia.gnu");

    if (result1 == 0 && result2 == 0 && result3 == 0) {
        cout << "Graficas generadas exitosamente:" << endl;
        cout << "- posicion_vs_tiempo.png" << endl;
        cout << "- velocidad_vs_tiempo.png" << endl;
        cout << "- energia_vs_tiempo.png" << endl;
    } else {
        cout << "Error: No se pudo generar las graficas." << endl;
        cout << "Pero los archivos de datos estan listos." << endl;
    }
}