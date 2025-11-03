#ifndef PROCESO_H
#define PROCESO_H

void solicitarDatos(double &L, double &x0, double &v0,
                    double &t0, double &tf, double &dt, double &e);
void validarDatos(double &L, double &x0, double &v0,
                  double &t0, double &tf, double &dt, double &e);
void simularMovimiento(double L, double x0, double v0,
                       double t0, double tf, double dt, double e);

#endif