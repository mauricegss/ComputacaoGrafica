#ifndef MATRIZ_H
#define MATRIZ_H

#include <QVector>
#include <QtMath>
#include "Structs.h"

class Matriz {
public:
    QVector<QVector<double>> matriz; // Matriz dinâmica onde cada coluna é um ponto
    QVector<QVector<double>> clone;
    QPair<double,double> vUp = {0,1};
    QString nome;

    Matriz(const QVector<Ponto3D>& pontos, const QString& nomeObjeto = "")
        : nome(nomeObjeto) {
        int numPontos = pontos.size();
        matriz.resize(4); // 3 linhas para x, y, e a linha de 1's
        clone.resize(4);

        for (int i = 0; i < 4; ++i) {
            matriz[i].resize(numPontos);
            clone[i].resize(numPontos);
        }

        // Preenche as coordenadas x, y e os 1's
        for (int i = 0; i < numPontos; ++i) {
            matriz[0][i] = pontos[i].x;
            matriz[1][i] = pontos[i].y;
            matriz[2][i] = pontos[i].z;
            matriz[3][i] = 1.0; // linha de 1's
            clone[0][i] = pontos[i].x;
            clone[1][i] = pontos[i].y;
            clone[2][i] = pontos[i].z;
            clone[3][i] = 1.0; // linha de 1's
        }
    }
};

QVector<QVector<double>> multiplicarMatrizes(const QVector<QVector<double>>& A, const QVector<QVector<double>>& B);
void transladar(Matriz& objeto, double dx, double dy, double dz);
void escalonar(Matriz& objeto, double sx, double sy, double sz);
void rotacionar(Matriz& objeto, double angulo, char torno);
void transladarClone(Matriz& objeto, double dx, double dy, double dz);
void rotacionarClone(Matriz window, Matriz& objeto, double angulo);
QVector<QVector<double>> normalizar(QVector<QVector<double>> matriz, QVector<QVector<double>> window, QVector<QVector<double>> viewPort);

#endif // MATRIZ_H
