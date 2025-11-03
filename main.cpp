#include <iostream>
#include <iomanip>
#include <fstream>
#include "../funcion/Proceso.h"
#include "../funcion/Grafica.h"

using namespace std;

int main() {
    double L, x0, v0, t0, tf, dt, e;

    // Ejecuta la simulación
    solicitarDatos(L, x0, v0, t0, tf, dt, e);
    validarDatos(L, x0, v0, t0, tf, dt, e);
    simularMovimiento(L, x0, v0, t0, tf, dt, e);

    // Generar gáficas estáticas
    cout << "\nPresione Enter para generar las graficas...";
    string temp;
    getline(cin, temp);  // Limpiar buffer
    getline(cin, temp);  // Esperar Enter
    
    generarGraficas();

    // Genera animación
    cout << "\nPresione Enter para generar la animacion GIF...";
    getline(cin, temp);
    
    generarAnimacion();

    cout << "\nPresione Enter para salir...";
    getline(cin, temp);

    return 0;
}