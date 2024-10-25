#include <QApplication>
#include <QWidget>
#include <QVector>
#include "MyWidget.h"
#include "Pontos.h"
#include "Matriz.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MyWidget myWidget;
    myWidget.show();

    QVector<Pontos> quad1 = { {100, 100}, {200,100}, {200,200}, {100,200} };
    myWidget.setObjetos(quad1);
    QVector<Pontos> quad2 = { {100, 100}, {200,100}, {200,200}, {100,200} };
    rotacionar(quad2, 0.785398);
    myWidget.setObjetos(quad2);


    myWidget.setWindowTitle("Computacao Gráfica");
    myWidget.resize(300,300);

    return app.exec();
}

