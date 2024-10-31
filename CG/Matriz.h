#ifndef MATRIZ_H
#define MATRIZ_H
#include <math.h>
#include <QVector>

/*
class Matriz{
double x,y;
    matriz (QVector<double> pontos(x_val, double y_val, 1) : x(x_val), y(y_val)) {}
Matriz QVector
}

*/

class Pontos {
public:
    double x, y;
    Pontos(double x_val, double y_val) : x(x_val), y(y_val) {}
};

class Matriz {
public:
    QVector<QVector<double>> matriz;
    QVector<QVector<double>> matrizI;

    Matriz(double x_val, double y_val) : matriz(3, QVector<double>(1)), matrizI(3, QVector<double>(3)) {
        matriz[0][0] = x_val;
        matriz[1][0] = y_val;
        matriz[2][0] = 1;
    }

    QVector<QVector<double>> matrizPonto() const {
        return matriz;
    }

    QVector<QVector<double>> matrizIdentidadeT(double dx, double dy) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if(i == j){
                    matrizI[i][j] = 1;
                }
                else if(i == 0 && j == 2){
                    matriz[i][j] = dx;
                }
                else if(i == 1 && j == 2){
                    matriz[i][j] = dy;
                }
                else{
                    matriz[i][j] = 0;
                }
            }
        }
        return matrizI;
    }

    QVector<QVector<double>> matrizIdentidadeE(double sx, double sy) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if(i == 0 && j == 0){
                    matriz[i][j] = sx;
                }
                else if(i == 1 && j == 1){
                    matriz[i][j] = sy;
                }
                else if(i == 2 && j == 2){
                    matriz[i][j] = 1;
                }
                else{
                    matriz[i][j] = 0;
                }
            }
        }
        return matrizI;
    }
};

#endif // MATRIZ_H
