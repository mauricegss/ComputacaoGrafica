#include <QPainter>

#ifndef PONTOS_H
#define PONTOS_H


class Pontos {

public:
    double x, y;

    // Construtor para inicializar os pontos
    Pontos(double x_val, double y_val) : x(x_val), y(y_val) {}

};

void Desenhar(QVector<Pontos> objeto);

#endif // PONTOS_H
