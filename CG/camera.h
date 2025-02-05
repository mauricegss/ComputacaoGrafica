#ifndef CAMERA_H
#define CAMERA_H

#include <QVector>
#include <QPointF>

class Camera {
public:
    Camera();
    void transladarCamera(double dx, double dy, double dz);
    void rotacionarCamera(double angulo, char eixo);
    void escalonarCamera(double sx, double sy, double sz);
    QVector<QVector<double>> aplicarTransformacao(const QVector<QVector<double>>& pontos);

private:
    QVector<QVector<double>> matrizTransformacao;
    void atualizarMatrizTransformacao();
};

#endif // CAMERA_H
