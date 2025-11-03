#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "../funcion/Proceso.h"

using namespace std;

const double EPSILON = 1.0e-9;

void solicitarDatos(double &L, double &x0, double &v0,double &t0, double &tf, double &dt, double &e) {
    cout << "Longitud de la caja L (m): ";
    cin >> L;
    cout << "Posicion inicial x0 (m): ";
    cin >> x0;
    cout << "Velocidad inicial v0 (m/s): ";
    cin >> v0;
    cout << "Tiempo inicial t0 (s): ";
    cin >> t0;
    cout << "Tiempo final tf (s): ";
    cin >> tf;
    cout << "Paso de tiempo dt (s): ";
    cin >> dt;
    cout << "Coeficiente de restitucion e (0 < e <= 1): ";
    cin >> e;
}

void validarDatos(double &L, double &x0, double &v0,double &t0, double &tf, double &dt, double &e) {
    // L > 0
    do {
        if (L <= 0.0) {
            cout << "L debe ser positivo. Vuelva a ingresar L: ";
            cin >> L;
        }
    } while (L <= 0.0);

    // 0 <= x0 <= L
    do {
        if (x0 < 0.0 || x0 > L) {
            cout << "x0 debe de estar [0, L]. Vuelva a ingresar x0: ";
            cin >> x0;
        }
    } while (x0 < 0.0 || x0 > L);

    // v0 != 0
    do {
        if (v0 == 0.0) {
            cout << "v0 no puede ser 0. Vuelva a ingresar v0: ";
            cin >> v0;
        }
    } while (v0 == 0.0);

    // tf > t0
    do {
        if (tf <= t0) {
            cout << "tf debe ser mayor que t0. Vuelva a ingresar tf: ";
            cin >> tf;
        }
    } while (tf <= t0);

    // 0 < dt < (tf - t0)
    do {
        if (dt <= 0.0 || dt >= (tf - t0)) {
            cout << "dt debe ser positivo y menor que (tf - t0). Ingrese dt: ";
            cin >> dt;
        }
    } while (dt <= 0.0 || dt >= (tf - t0));

    // 0 < e <= 1
    do {
        if (e <= 0.0 || e > 1.0) {
            cout << "e debe estar en (0, 1]. Ingrese e: ";
            cin >> e;
        }
    } while (e <= 0.0 || e > 1.0);
}

void simularMovimiento(double L, double x0, double v0,double t0, double tf, double dt, double e) {
    
    ofstream myfile("simulacion.txt");
    if (!myfile.is_open()) {
        cout << "Error. No se pudo abrir el archivo para escritura." << endl;
        return;
    }

    cout << fixed << setprecision(5);
    cout << setw(12) << "t"
         << setw(15) << "x"
         << setw(15) << "v"
         << setw(20) << "Ec" << '\n';

    myfile << fixed << setprecision(5);
    myfile << setw(12) << "t"
           << setw(15) << "x"
           << setw(15) << "v"
           << setw(20) << "Energia_Cinetica" << '\n';

    double t = t0, x = x0, v = v0;
    int i = 0;
    int n_colisiones = 0;

    while (t <= tf + EPSILON) {
        double energia_cinetica = 0.5 * v * v;

        cout << setw(12) << t
             << setw(15) << x
             << setw(15) << v
             << setw(20) << energia_cinetica << '\n';

        myfile << setw(12) << t
               << setw(15) << x
               << setw(15) << v
               << setw(20) << energia_cinetica << '\n';

        double x_nueva = x + v * dt;

        if (x_nueva < 0.0) {
            x = 0.0;
            v = -e * v;
            n_colisiones++;
        } else if (x_nueva > L) {
            x = L;
            v = -e * v;
            n_colisiones++;
        } else {
            x = x_nueva;
        }

        i++;
        t = t0 + i * dt;
    }

    myfile.close();

    cout << "\n=== SIMULACION COMPLETADA ===" << endl;
    cout << "Total de colisiones: " << n_colisiones << endl;
    cout << "Coeficiente de restitucion: " << e << endl;
    cout << "Datos guardados en 'simulacion.txt'" << endl;
}