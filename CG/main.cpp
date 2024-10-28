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

    myWidget.setWindowTitle("Computação Gráfica");
    myWidget.resize(1000,800);

    return app.exec();
}
