#include "camera.h"
#include <cmath>
#include <QDebug>

Camera::Camera() {
    // Inicializa a matriz de transformação como uma matriz identidade
    matrizTransformacao = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
}

void Camera::transladarCamera(double dx, double dy, double dz) {
    QVector<QVector<double>> translacao = {
        {1, 0, 0, dx},
        {0, 1, 0, dy},
        {0, 0, 1, dz},
        {0, 0, 0, 1}
    };
    // Multiplica a matriz de transformação atual pela matriz de translação
    QVector<QVector<double>> resultado(4, QVector<double>(4, 0));
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                resultado[i][j] += matrizTransformacao[i][k] * translacao[k][j];
            }
        }
    }
    matrizTransformacao = resultado;
}

void Camera::rotacionarCamera(double angulo, char eixo) {
    double rad = qDegreesToRadians(angulo);
    double cosA = std::cos(rad);
    double sinA = std::sin(rad);

    QVector<QVector<double>> rotacao;

    switch (eixo) {
    case 'x':
        rotacao = {
            {1, 0, 0, 0},
            {0, cosA, -sinA, 0},
            {0, sinA, cosA, 0},
            {0, 0, 0, 1}
        };
        break;
    case 'y':
        rotacao = {
            {cosA, 0, sinA, 0},
            {0, 1, 0, 0},
            {-sinA, 0, cosA, 0},
            {0, 0, 0, 1}
        };
        break;
    case 'z':
        rotacao = {
            {cosA, -sinA, 0, 0},
            {sinA, cosA, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        };
        break;
    default:
        qDebug() << "Eixo de rotação inválido!";
        return;
    }

    // Multiplica a matriz de transformação atual pela matriz de rotação
    QVector<QVector<double>> resultado(4, QVector<double>(4, 0));
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                resultado[i][j] += matrizTransformacao[i][k] * rotacao[k][j];
            }
        }
    }
    matrizTransformacao = resultado;
}

void Camera::escalonarCamera(double sx, double sy, double sz) {
    QVector<QVector<double>> escala = {
        {sx, 0, 0, 0},
        {0, sy, 0, 0},
        {0, 0, sz, 0},
        {0, 0, 0, 1}
    };
    // Multiplica a matriz de transformação atual pela matriz de escala
    QVector<QVector<double>> resultado(4, QVector<double>(4, 0));
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                resultado[i][j] += matrizTransformacao[i][k] * escala[k][j];
            }
        }
    }
    matrizTransformacao = resultado;
}

QVector<QVector<double>> Camera::aplicarTransformacao(const QVector<QVector<double>>& pontos) {
    QVector<QVector<double>> pontosTransformados = pontos;
    for (int i = 0; i < pontos[0].size(); ++i) {
        double x = pontos[0][i];
        double y = pontos[1][i];
        double z = pontos[2][i];
        double w = 1;

        double xT = matrizTransformacao[0][0] * x + matrizTransformacao[0][1] * y + matrizTransformacao[0][2] * z + matrizTransformacao[0][3] * w;
        double yT = matrizTransformacao[1][0] * x + matrizTransformacao[1][1] * y + matrizTransformacao[1][2] * z + matrizTransformacao[1][3] * w;
        double zT = matrizTransformacao[2][0] * x + matrizTransformacao[2][1] * y + matrizTransformacao[2][2] * z + matrizTransformacao[2][3] * w;

        pontosTransformados[0][i] = xT;
        pontosTransformados[1][i] = yT;
        pontosTransformados[2][i] = zT;
    }
    return pontosTransformados;
}
