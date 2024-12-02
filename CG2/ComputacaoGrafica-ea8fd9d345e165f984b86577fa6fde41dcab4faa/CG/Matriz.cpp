#include "Matriz.h"
#include "displayFile.h"

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
    objeto.matriz = multiplicarMatrizes(matrizTranslacao, objeto.matriz);
}

void escalonar(Matriz& objeto, double sx, double sy) {

    // Calcula o centro geométrico
    double cx = 0, cy = 0;
    int numPontos = objeto.matriz[0].size();
    for (int i = 0; i < numPontos; ++i) {
        cx += objeto.matriz[0][i];
        cy += objeto.matriz[1][i];
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
    objeto.matriz = multiplicarMatrizes(matrizEscalonamento, objeto.matriz);
}

void rotacionar(Matriz& objeto, double angulo) {

    // Calcula o centro geométrico
    double cx = 0, cy = 0;
    int numPontos = objeto.matriz[0].size();
    for (int i = 0; i < numPontos; ++i) {
        cx += objeto.matriz[0][i];
        cy += objeto.matriz[1][i];
    }
    cx /= numPontos;
    cy /= numPontos;

    // Matriz de rotação em torno do centro geométrico
    double cosAng = cos(qDegreesToRadians(angulo));
    double sinAng = sin(qDegreesToRadians(angulo));
    QVector<QVector<double>> matrizRotacao = {
        {cosAng, -sinAng, cx * (1 - cosAng) + cy * sinAng},
        {sinAng, cosAng, cy * (1 - cosAng) - cx * sinAng},
        {0, 0, 1}
    };

    double vx = objeto.vUp.first;
    double vy = objeto.vUp.second;
    objeto.vUp.first = cosAng * vx - sinAng * vy;
    objeto.vUp.second = sinAng * vx + cosAng * vy;

    // Multiplica a matriz do objeto pela matriz de rotação
    objeto.matriz = multiplicarMatrizes(matrizRotacao, objeto.matriz);
}

void transladarClone(Matriz& objeto, double dx, double dy) {
    // Matriz de translação
    QVector<QVector<double>> matrizTranslacao = {
        {1, 0, dx},
        {0, 1, dy},
        {0, 0, 1}
    };

    // Multiplica a matriz do objeto pela matriz de translação
    objeto.clone = multiplicarMatrizes(matrizTranslacao, objeto.clone);

}

void rotacionarClone(Matriz window, Matriz& objeto, double angulo) {

    // Calcula o centro geométrico
    double cx = 0, cy = 0;
    int numPontos = window.clone[0].size();
    for (int i = 0; i < numPontos; ++i) {
        cx += window.clone[0][i];
        cy += window.clone[1][i];
    }
    cx /= numPontos;
    cy /= numPontos;

    // Matriz de rotação em torno do centro geométrico
    double cosAng = cos(qDegreesToRadians(angulo));
    double sinAng = sin(qDegreesToRadians(angulo));
    QVector<QVector<double>> matrizRotacao = {
        {cosAng, -sinAng, cx * (1 - cosAng) + cy * sinAng},
        {sinAng, cosAng, cy * (1 - cosAng) - cx * sinAng},
        {0, 0, 1}
    };

    // Multiplica a matriz do objeto pela matriz de rotação
    objeto.clone = multiplicarMatrizes(matrizRotacao, objeto.clone);
}
