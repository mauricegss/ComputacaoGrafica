#include <QApplication>
#include "mainwindow.h"
#include "Matriz.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    // Inicializando pontos diretamente como pares
    QVector<QPair<double, double>> quad1Pontos = { {100, 100}, {200, 100}, {200, 200}, {100, 200} };
    Matriz quad1(quad1Pontos);
    mainWindow.adicionarObjeto(quad1);

    QVector<QPair<double, double>> tri1Pontos = { {300, 100}, {500, 100}, {500, 300} };
    Matriz tri1(tri1Pontos);
    mainWindow.adicionarObjeto(tri1);

    QVector<QPair<double, double>> ret1Pontos = { {100, 400}, {400, 400} };
    Matriz ret1(ret1Pontos);
    mainWindow.adicionarObjeto(ret1);

    mainWindow.setWindowTitle("Computação Gráfica");
    mainWindow.resize(600, 600);

    return app.exec();
}
