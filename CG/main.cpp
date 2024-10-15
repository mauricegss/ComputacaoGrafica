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

    QVector<QPoint> point = { QPoint(110, 75) };
    displayFile.addObject(DisplayObject("Point1", PointType, point));

    //TriForce (Linhas)
    for(int i=0;i<50;i++){
        QVector<QPoint> triforce1 = { QPoint(60+i, 55+i), QPoint(60-i,55+i) };
        displayFile.addObject(DisplayObject("Esquerda", LineType, triforce1));
    }
    for(int i=0;i<50;i++){
        QVector<QPoint> triforce2 = { QPoint(160+i, 55+i), QPoint(160-i, 55+i) };
        displayFile.addObject(DisplayObject("Direita", LineType, triforce2));
    }
    for(int i=0;i<50;i++){
        QVector<QPoint> triforce3 = { QPoint(110+i, i+5), QPoint(110-i,i+5) };
        displayFile.addObject(DisplayObject("Cima", LineType, triforce3));
    }

    // Bordas (Poligonos)
    QVector<QPoint> borda_ext = { QPoint(110, 0), QPoint(0, 110), QPoint(220, 110) };
    displayFile.addObject(DisplayObject("Externa", PolygonType, borda_ext));
    QVector<QPoint> borda_int = { QPoint(70, 60), QPoint(150, 60), QPoint(110, 100) };
    displayFile.addObject(DisplayObject("Interna", PolygonType, borda_int));

    // Criando o CanvasWidget
    CanvasWidget* canvas = new CanvasWidget();
    canvas->setDisplayFile(&displayFile);

    // Definindo o CanvasWidget como a central da janela
    window.setCentralWidget(canvas);
    window.resize(220, 115);
    window.show();

    return app.exec();
}
