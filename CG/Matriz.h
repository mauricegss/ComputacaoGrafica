#ifndef MATRIZ_H
#define MATRIZ_H

#include <math.h>
#include <QVector>

class Matriz {
public:
    double x, y; // coordenadas
    // Matriz 2x1
    Matriz(double x_val, double y_val) : x(x_val), y(y_val) {}
};

void centroGeometrico(QVector<Matriz>& objeto, double& xsave, double& ysave);
void transladar(QVector<Matriz>& objeto, double dx, double dy);
void escalonar(QVector<Matriz>& objeto, double sx, double sy);
void rotacionar(QVector<Matriz>& objeto, double angulo);
void aplicarMatriz(QVector<Matriz>& objeto, const QVector<QVector<double>>& matriz);

#endif // MATRIZ_H
