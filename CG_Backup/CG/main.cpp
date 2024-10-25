// main.cpp
#include <QApplication>
#include <QMainWindow>
#include "tela.h"
#include "displayfile.h"
#include "displayobject.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QMainWindow window;

    // criação do DisplayFile
    DisplayFile displayFile;

    // Adicionando objetos ao DisplayFile

    QVector<QPoint> ponto = { QPoint(110, 75) };
    displayFile.addObject(DisplayObject("Point1", PointType, ponto));

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

    // Criando o Tela
    Tela* canvas = new Tela();
    canvas->setDisplayFile(&displayFile);

    // centralizando o CanvasWidget
    window.setCentralWidget(canvas);
    window.resize(220, 115);
    window.show();

    return app.exec();
}


