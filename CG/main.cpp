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
    myWidget.adicionarObjeto(quad1);

    QVector<Pontos> quad2 = { {100, 100}, {200,100}, {200,200}, {100,200} };
    escalonar(quad2,2,2);
    myWidget.adicionarObjeto(quad2);

    rotacionar(quad2, 0.785398);
    myWidget.adicionarObjeto(quad2);

    myWidget.setWindowTitle("Computação Gráfica");
    myWidget.resize(300,300);

    return app.exec();
}

