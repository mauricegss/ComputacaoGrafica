#ifndef MATRIZ_H
#define MATRIZ_H

#include <QVector>
#include <QString>
#include <math.h>

class Matriz {
public:
    QVector<QVector<double>> matriz;         // Matriz dinâmica onde cada coluna é um ponto
    QVector<QVector<double>> normalizada;    // Matriz após a transformação da viewport
    QString nome;                            // Nome do objeto

    // Construtor que agora também recebe o nome
    Matriz(const QVector<QPair<double, double>>& pontos, const QString& nomeObjeto = "")
        : nome(nomeObjeto) {
        int numPontos = pontos.size();
        matriz.resize(3);            // 3 linhas para x, y, e a linha de 1's
        normalizada.resize(3);       // Inicializa a matriz normalizada

        for (int i = 0; i < 3; ++i) {
            matriz[i].resize(numPontos);
            normalizada[i].resize(numPontos);
        }

        // Preenche as coordenadas x, y e os 1's
        for (int i = 0; i < numPontos; ++i) {
            matriz[0][i] = pontos[i].first;
            matriz[1][i] = pontos[i].second;
            matriz[2][i] = 1.0; // linha de 1's
        }
    }

    // Método de normalização usando a matriz viewport
    QVector<QVector<double>> normalizar(QVector<QVector<double>> matriz, Matriz viewPort) {
        int numPontos = matriz[0].size();
        QVector<QVector<double>> resultado;
        resultado.resize(3);

        for (int i = 0; i < 3; ++i) {
            resultado[i].resize(numPontos);
        }

        // Preenche as coordenadas x, y e os 1's aplicando a transformação de normalização
        for (int i = 0; i < numPontos; ++i) {
            resultado[0][i] = ((matriz[0][i] - viewPort.matriz[0][0]) / (viewPort.matriz[0][1] - viewPort.matriz[0][0])) * (600 - 0);
            resultado[1][i] = ((1 - (matriz[1][i] - viewPort.matriz[1][0]) / (viewPort.matriz[1][2] - viewPort.matriz[1][0]))) * (600 - 0);
            resultado[2][i] = 1.0; // linha de 1's
        }

        return resultado;
    }
};

// Declarações das funções de operações com matrizes
QVector<QVector<double>> multiplicarMatrizes(const QVector<QVector<double>>& A, const QVector<QVector<double>>& B);
void transladar(Matriz& objeto, double dx, double dy);
void escalonar(Matriz& objeto, double sx, double sy);
void rotacionar(Matriz& objeto, double angulo);

#endif // MATRIZ_H
