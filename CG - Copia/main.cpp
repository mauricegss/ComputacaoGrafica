#include <QApplication>
#include "mainwindow.h"
#include "Matriz.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;

    // Inicializando pontos diretamente como pares, agora com o nome
    QVector<QPair<double, double>> quad1Pontos = { {0, 0}, {100, 0}, {100, 100}, {0, 100} };
    Matriz quad1(quad1Pontos, "Quadrado Legal"); // Passando o nome
    mainWindow.adicionarObjeto(quad1);

    QVector<QPair<double, double>> tri1Pontos = { {300, 100}, {500, 100}, {500, 300} };
    Matriz tri1(tri1Pontos, "Triangulo Legal"); // Passando o nome
    mainWindow.adicionarObjeto(tri1);

    QVector<QPair<double, double>> ret1Pontos = { {100, 400}, {400, 400} };
    Matriz ret1(ret1Pontos, "Reta Legal"); // Passando o nome
    mainWindow.adicionarObjeto(ret1);

    // Window Config
    mainWindow.atualizarDisplayMatriz();
    mainWindow.showMaximized();
    mainWindow.setWindowTitle("Computação Gráfica");

    return app.exec();
}
