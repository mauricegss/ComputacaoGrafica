#include <QApplication>
#include "mainwindow.h"
#include "matriz.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    // Inicializando pontos diretamente como pares
    QVector<QPair<double, double>> pontos = { {100, 100}, {250, 100}, {250, 250}, {100, 250} };
    Matriz window(pontos);
    mainWindow.adicionarObjeto(window, "Window");

    pontos = { {100, 100}, {400, 100}, {400, 400}, {100, 400}  };
    Matriz viewPort(pontos);
    mainWindow.adicionarObjeto(viewPort, "Viewport");

    pontos = { {20, 120}, {90, 300} };
    Matriz quad1(pontos);
    mainWindow.adicionarObjeto(quad1, "Quadrado");


    pontos = { {90 , 100}, {150, 250}};
    Matriz tri1(pontos);
    mainWindow.adicionarObjeto(tri1, "Triangulo");

    pontos = { {120, 60}, {180, 80} };
    Matriz ret1(pontos);
    mainWindow.adicionarObjeto(ret1, "Retangulo");

    mainWindow.setWindowTitle("Computação Gráfica");
    mainWindow.resize(600, 600);

    return app.exec();
}
