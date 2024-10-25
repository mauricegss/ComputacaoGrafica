#ifndef MATRIZ_H
#define MATRIZ_H

#include "Pontos.h"
#include "MyWidget.h"
#include <math.h>
#include <QVector>

void transladar(QVector<Pontos>& objeto, double X, double Y);

void escalar(QVector<Pontos>& objeto, double X, double Y);

void rotacionar(QVector<Pontos>& objeto, double X);


#endif // MATRIZ_H
