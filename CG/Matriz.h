#ifndef MATRIZ_H
#define MATRIZ_H

#include <math.h>
#include <QVector>

class Pontos {
public:
    double x, y;

    // Construtor para inicializar os pontos
    Pontos(double x_val, double y_val) : x(x_val), y(y_val) {}
};

void centroGeometrico(QVector<Pontos>& objeto, double& xsave, double& ysave);
void transladar(QVector<Pontos>& objeto, double dx, double dy);
void escalonar(QVector<Pontos>& objeto, double sx, double sy);
void rotacionar(QVector<Pontos>& objeto, double angulo);
void aplicarMatriz(QVector<Pontos>& objeto, const QVector<QVector<double>>& matriz);

#endif // MATRIZ_H
