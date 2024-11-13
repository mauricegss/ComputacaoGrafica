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

    transladar(objeto, -cx, -cy);

    // Matriz de escalonamento em torno do centro geométrico
    QVector<QVector<double>> matrizEscalonamento = {
        {sx, 0, 0},
        {0, sy, 0},
        {0, 0, 1}
    };

    // Multiplica a matriz do objeto pela matriz de escalonamento
    objeto.normalizada = multiplicarMatrizes(matrizEscalonamento, objeto.normalizada);

    transladar(objeto, cx, cy);
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

    transladar(objeto, -cx, -cy);

    // Matriz de rotação em torno do centro geométrico
    double cosAng = cos(angulo);
    double sinAng = sin(angulo);
    QVector<QVector<double>> matrizRotacao = {
        //{cosAng, -sinAng, cx * (1 - cosAng) + cy * sinAng},
        //{sinAng, cosAng, cy * (1 - cosAng) - cx * sinAng},
        {cosAng, -sinAng, 0},
        {sinAng, cosAng, 0},
        {0, 0, 1}
    };

    // Multiplica a matriz do objeto pela matriz de rotação
    objeto.normalizada = multiplicarMatrizes(matrizRotacao, objeto.normalizada);

    transladar(objeto, cx, cy);
}

void centralizarTudo(QVector<Matriz>& objetos) {

    // Calcula o centro geométrico do primeiro objeto (pode ser ajustado para todos)
    double cx = 0;
    double cy = 0;
    int numPontos = objetos[0].normalizada[0].size();
    double angulo;

    for (int i = 0; i < numPontos; ++i) {
        cx += objetos[0].normalizada[0][i];
        cy += objetos[0].normalizada[1][i];
    }
    cx /= numPontos;
    cy /= numPontos;
    angulo = acharAnguloVup(objetos[0], cx, cy);
    // Translada todos os objetos para centralizar
    for (int i = 0; i < objetos.size(); ++i) {
        transladar(objetos[i], -cx, -cy);
    }
    // rotaciona todos os objetos para centralizar
    for (int i = 0; i < objetos.size(); ++i) {
        rotacionar(objetos[i], -angulo);
    }
    // escalona todos os objetos para centralizar
    for (int i = 0; i < objetos.size(); ++i) {
        escalonar(objetos[i], -1,1);
    }
}

double acharAnguloVup(Matriz& objeto, int cx, int cy) {
    // Calcula o ponto médio do objeto como o ponto "para cima"
    double px = (objeto.matriz[0][0] + objeto.matriz[1][0]) / 2;
    double py = objeto.matriz[0][1];

    // Calcula o vetor v_up entre o centro (cx, cy) e o ponto (px, py)
    double vup_x = px - cx;
    double vup_y = py - cy;

    // Normaliza o vetor v_up
    double magnitude = std::sqrt(vup_x * vup_x + vup_y * vup_y);
    if (magnitude == 0) return 0.0; // Evita divisão por zero, assume ângulo zero se v_up for nulo

    vup_x /= magnitude;
    vup_y /= magnitude;

    // Calcula o ângulo entre v_up e o eixo Y usando atan2
    double theta = std::atan2(vup_x, vup_y); // Note a ordem: vup_x depois vup_y

    // Retorna o ângulo em radianos
    return theta;
}


