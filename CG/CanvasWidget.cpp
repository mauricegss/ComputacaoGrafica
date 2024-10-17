// CanvasWidget.cpp
#include "CanvasWidget.h"
#include <QPainter>

CanvasWidget::CanvasWidget(QWidget *parent) : QWidget(parent), displayFile(nullptr) {}

void CanvasWidget::setDisplayFile(DisplayFile* displayFile) {
    this->displayFile = displayFile;
    update();  // solicita a atualização da tela
}

void CanvasWidget::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);

    if (!displayFile) return;

    QPainter painter(this);
    QVector<DisplayObject> objects = displayFile->getObjects();

    for (const DisplayObject& obj : objects) {
        QVector<QPoint> points = obj.getPontos();

        switch (obj.getTipo()) {
        case PointType:
            painter.drawPoint(points[0]);
            break;
        case LineType:
            if (points.size() >= 2) {
                painter.drawLine(points[0], points[1]);
            }
            break;
        case PolygonType:
            if (points.size() >= 3) {
                painter.drawPolygon(points.data(), points.size());
            }
            break;
        }
    }
}
