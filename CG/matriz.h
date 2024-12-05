#ifndef MATRIZ_H
#define MATRIZ_H

#include <QVector>
#include <QtMath>

class Matriz {
public:
    QVector<QVector<double>> matriz; // Matriz dinâmica onde cada coluna é um ponto
    QVector<QVector<double>> clone;
    QPair<double,double> vUp = {0,1};
    QString nome;

    Matriz(const QVector<QPair<double, double>>& pontos, const QString& nomeObjeto = "")
        : nome(nomeObjeto) {
        int numPontos = pontos.size();
        matriz.resize(3); // 3 linhas para x, y, e a linha de 1's
        clone.resize(3);

        for (int i = 0; i < 3; ++i) {
            matriz[i].resize(numPontos);
            clone[i].resize(numPontos);
        }

        // Preenche as coordenadas x, y e os 1's
        for (int i = 0; i < numPontos; ++i) {
            matriz[0][i] = pontos[i].first;
            matriz[1][i] = pontos[i].second;
            matriz[2][i] = 1.0; // linha de 1's
            clone[0][i] = pontos[i].first;
            clone[1][i] = pontos[i].second;
            clone[2][i] = 1.0; // linha de 1's
        }
    }
};

QVector<QVector<double>> multiplicarMatrizes(const QVector<QVector<double>>& A, const QVector<QVector<double>>& B);
void transladar(Matriz& objeto, double dx, double dy);
void escalonar(Matriz& objeto, double sx, double sy);
void rotacionar(Matriz& objeto, double angulo);
void transladarClone(Matriz& objeto, double dx, double dy);
void rotacionarClone(Matriz window, Matriz& objeto, double angulo);
QVector<QVector<double>> normalizar(QVector<QVector<double>> matriz, QVector<QVector<double>> window, QVector<QVector<double>> viewPort);

#endif // MATRIZ_H
