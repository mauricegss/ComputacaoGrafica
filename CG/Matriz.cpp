#include "Matriz.h"

void centroGeometrico(QVector<Pontos>& objeto, double& xsave, double& ysave) {
    double area = 0.0;
    xsave = 0;
    ysave = 0;
    for (int i = 0; i < objeto.size(); i++) {
        int j = (i + 1) % objeto.size();
        double save = objeto[i].x * objeto[j].y - objeto[j].x * objeto[i].y;
        area += save;
        xsave += (objeto[i].x + objeto[j].x) * save;
        ysave += (objeto[i].y + objeto[j].y) * save;
    }
    area *= 0.5;
    xsave /= (6.0 * area);
    ysave /= (6.0 * area);
}

void aplicarMatriz(QVector<Pontos>& objeto, const QVector<QVector<double>>& matriz) {
    for (auto& ponto : objeto) {
        double x = ponto.x;
        double y = ponto.y;
        ponto.x = matriz[0][0] * x + matriz[0][1] * y + matriz[0][2];
        ponto.y = matriz[1][0] * x + matriz[1][1] * y + matriz[1][2];
    }
}

void transladar(QVector<Pontos>& objeto, double dx, double dy) {
    QVector<QVector<double>> matriz = {
        {1, 0, dx},
        {0, 1, dy},
        {0, 0, 1}
    };
    aplicarMatriz(objeto, matriz);
}

void escalonar(QVector<Pontos>& objeto, double sx, double sy) {
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

void rotacionar(QVector<Pontos>& objeto, double angulo) {
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
