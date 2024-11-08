#include <QApplication>
#include "MyWidget.h"
#include "Matriz.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MyWidget myWidget;
    myWidget.show();

    // Inicializando pontos diretamente como pares
    QVector<QPair<double, double>> quad1Pontos = { {100, 100}, {200, 100}, {200, 200}, {100, 200} };
    Matriz quad1(quad1Pontos);
    myWidget.adicionarObjeto(quad1);

    QVector<QPair<double, double>> tri1Pontos = { {300, 100}, {500, 100}, {500, 300} };
    Matriz tri1(tri1Pontos);
    myWidget.adicionarObjeto(tri1);

    QVector<QPair<double, double>> ret1Pontos = { {100, 400}, {400, 400}};
    Matriz ret1(ret1Pontos);
    myWidget.adicionarObjeto(ret1);

    myWidget.setWindowTitle("Computação Gráfica");
    myWidget.resize(600, 600);

    return app.exec();
}
