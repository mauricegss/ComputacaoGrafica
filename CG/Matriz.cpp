#include "Matriz.h"

// Função auxiliar para multiplicar duas matrizes
QVector<QVector<double>> multiplicarMatrizes(const QVector<QVector<double>>& A, const QVector<QVector<double>>& B) {
    int linhasA = A.size();
    int colunasA = A[0].size();
    int colunasB = B[0].size();

    QVector<QVector<double>> resultado(linhasA, QVector<double>(colunasB, 0.0));

    for (int i = 0; i < linhasA; ++i) {
        for (int j = 0; j < colunasB; ++j) {
            for (int k = 0; k < colunasA; ++k) {
                resultado[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return resultado;
}

void transladar(Matriz& objeto, double dx, double dy) {
    // Matriz de translação
    QVector<QVector<double>> matrizTranslacao = {
        {1, 0, dx},
        {0, 1, dy},
        {0, 0, 1}
    };

    // Multiplica a matriz do objeto pela matriz de translação
    objeto.normalizada = multiplicarMatrizes(matrizTranslacao, objeto.normalizada);
}

void escalonar(Matriz& objeto, double sx, double sy) {

    // Calcula o centro geométrico
    double cx = 0, cy = 0;
    int numPontos = objeto.normalizada[0].size();
    for (int i = 0; i < numPontos; ++i) {
        cx += objeto.normalizada[0][i];
        cy += objeto.normalizada[1][i];
    }
    cx /= numPontos;
    cy /= numPontos;

    // Matriz de escalonamento em torno do centro geométrico
    QVector<QVector<double>> matrizEscalonamento = {
        {sx, 0, cx * (1 - sx)},
        {0, sy, cy * (1 - sy)},
        {0, 0, 1}
    };

    // Multiplica a matriz do objeto pela matriz de escalonamento
    objeto.normalizada = multiplicarMatrizes(matrizEscalonamento, objeto.normalizada);
}

void rotacionar(Matriz& objeto, double angulo) {

    angulo = angulo * M_PI /180.0;
    // Calcula o centro geométrico
    double cx = 0, cy = 0;
    int numPontos = objeto.normalizada[0].size();
    for (int i = 0; i < numPontos; ++i) {
        cx += objeto.normalizada[0][i];
        cy += objeto.normalizada[1][i];
    }
    cx /= numPontos;
    cy /= numPontos;

    // Matriz de rotação em torno do centro geométrico
    double cosAng = cos(angulo);
    double sinAng = sin(angulo);
    QVector<QVector<double>> matrizRotacao = {
        {cosAng, -sinAng, cx * (1 - cosAng) + cy * sinAng},
        {sinAng, cosAng, cy * (1 - cosAng) - cx * sinAng},
        //{cosAng, -sinAng, 0},
        //{sinAng, cosAng, 0},
        {0, 0, 1}
    };

    // Multiplica a matriz do objeto pela matriz de rotação
    objeto.normalizada = multiplicarMatrizes(matrizRotacao, objeto.normalizada);
}
