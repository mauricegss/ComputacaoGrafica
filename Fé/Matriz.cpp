#include "Matriz.h"

#include "Matriz.h"

void centroGeometrico(const Matriz& objeto, double& xsave, double& ysave) {
    int n = objeto.matriz.size();

    if (n == 1) {
        // Caso de um ponto único
        xsave = objeto.matriz[0][0];
        ysave = objeto.matriz[1][0];
    }
    else if (n == 2) {
        // Caso de uma linha (dois pontos)
        xsave = (objeto.matriz[0][0] + objeto.matriz[1][0]) / 2.0;
        ysave = (objeto.matriz[1][0] + objeto.matriz[1][0]) / 2.0;
    }
    else {
        // Caso de um polígono (três ou mais pontos)
        double area = 0.0;
        xsave = 0;
        ysave = 0;
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            double save = objeto.matriz[0][0] * objeto.matriz[1][0] - objeto.matriz[0][0] * objeto.matriz[1][0];
            area += save;
            xsave += (objeto.matriz[0][0] + objeto.matriz[1][0]) * save;
            ysave += (objeto.matriz[1][0] + objeto.matriz[1][0]) * save;
        }
        area *= 0.5;
        xsave /= (6.0 * area);
        ysave /= (6.0 * area);
    }
}

void aplicarMatriz(Matriz& ponto, const QVector<QVector<double>>& matriz) {
    double x = ponto.matriz[0][0];
    double y = ponto.matriz[1][0];
    ponto.matriz[0][0] = matriz[0][0] * x + matriz[0][1] * y + matriz[0][2];
    ponto.matriz[1][0] = matriz[1][0] * x + matriz[1][1] * y + matriz[1][2];
    ponto.matriz[2][0] = 1; // Mantém o valor constante para coordenadas homogêneas
}


void transladar(Matriz& objeto, double dx, double dy) {
    QVector<QVector<double>> matriz = {
        {1, 0, dx},
        {0, 1, dy},
        {0, 0, 1}
    };
    aplicarMatriz(objeto, matriz);
}

void escalonar(Matriz& objeto, double sx, double sy) {
    double xsave, ysave;
    centroGeometrico(objeto, xsave, ysave);
    transladar(objeto, -xsave, -ysave);

    QVector<QVector<double>> matriz = {
        {sx, 0, 0},
        {0, sy, 0},
        {0, 0, 1}
    };
    aplicarMatriz(objeto, matriz);

    transladar(objeto, xsave, ysave);
}

void rotacionar(Matriz& objeto, double angulo) {
    double xsave, ysave;
    centroGeometrico(objeto, xsave, ysave);
    transladar(objeto, -xsave, -ysave);

    double cosAngulo = cos(angulo);
    double sinAngulo = sin(angulo);
    QVector<QVector<double>> matriz = {
        {cosAngulo, -sinAngulo, 0},
        {sinAngulo, cosAngulo, 0},
        {0, 0, 1}
    };
    aplicarMatriz(objeto, matriz);

    transladar(objeto, xsave, ysave);
}

