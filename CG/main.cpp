// main.cpp
#include <QApplication>
#include <QMainWindow>
#include "CanvasWidget.h"
#include "DisplayFile.h"
#include "DisplayObject.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QMainWindow window;

    // Criação do DisplayFile
    DisplayFile displayFile;

    // Adicionando objetos ao DisplayFile
    //QVector<QPoint> point = { QPoint(100, 100) };
    //displayFile.addObject(DisplayObject("Point1", PointType, point));

    for(int i=0;i<=200;i++){
        QVector<QPoint> line = { QPoint(50+i, i), QPoint(50-i,i) };
        displayFile.addObject(DisplayObject("Line1", LineType, line));
    }

    //QVector<QPoint> polygon = { QPoint(200, 200), QPoint(250, 250), QPoint(250, 200) };
    //displayFile.addObject(DisplayObject("Polygon1", PolygonType, polygon));

    // Criando o CanvasWidget
    CanvasWidget* canvas = new CanvasWidget();
    canvas->setDisplayFile(&displayFile);

    // Definindo o CanvasWidget como a central da janela
    window.setCentralWidget(canvas);
    window.resize(400, 400);
    window.show();

    return app.exec();
}
