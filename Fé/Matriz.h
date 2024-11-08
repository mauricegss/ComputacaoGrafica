#ifndef MATRIZ_H
#define MATRIZ_H

#include <QVector>
#include <math.h>

class Matriz {
public:
    QVector<QVector<double>> matriz; // Matriz dinâmica onde cada coluna é um ponto

    Matriz(const QVector<QPair<double, double>>& pontos) {
        int numPontos = pontos.size();
        matriz.resize(3); // 3 linhas para x, y, e a linha de 1's

        for (int i = 0; i < 3; ++i) {
            matriz[i].resize(numPontos);
        }

        // Preenche as coordenadas x, y e os 1's
        for (int i = 0; i < numPontos; ++i) {
            matriz[0][i] = pontos[i].first;
            matriz[1][i] = pontos[i].second;
            matriz[2][i] = 1.0; // linha de 1's
        }
    }
};

void centroGeometrico(const Matriz& objeto, double& xsave, double& ysave);
void transladar(Matriz& objeto, double dx, double dy);
void escalonar(Matriz& objeto, double sx, double sy);
void rotacionar(Matriz& objeto, double angulo);
void aplicarMatriz(Matriz& objeto, const QVector<QVector<double>>& transformacao);



#endif // MATRIZ_H
