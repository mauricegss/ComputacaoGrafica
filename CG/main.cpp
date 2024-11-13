#include <QApplication>
#include "mainwindow.h"
#include "Matriz.h"
#include <QFrame>

QVector<QPair<double, double>> windowPontos = { {100, 100}, {200, 100}, {200, 200}, {100, 200} };
Matriz window(windowPontos, "window");

int X2MAX = 610; //coordenadas viewport
int X2MIN = 50;
int Y2MAX = 610;
int Y2MIN = 50;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;

    // Inicializando pontos diretamente como pares
    //window.normalizada = window.normalizar(window.matriz, window, X2MAX, X2MIN, Y2MAX, Y2MIN);
    window.normalizada = window.matriz;
    mainWindow.adicionarObjeto(window);

    QVector<QPair<double, double>> quad1Pontos = { {100, 100}, {200, 100}, {200, 200}, {100, 200} };
    Matriz quad1(quad1Pontos, "Quadradin");
    //quad1.normalizada = quad1.normalizar(quad1.matriz, window, X2MAX, X2MIN, Y2MAX, Y2MIN);
    quad1.normalizada = quad1.matriz;
    mainWindow.adicionarObjeto(quad1);

    QVector<QPair<double, double>> tri1Pontos = { {300, 100}, {500, 100}, {500, 300} };
    Matriz tri1(tri1Pontos, "Tri Retangulo");
    //tri1.normalizada = tri1.normalizar(tri1.matriz, window, X2MAX, X2MIN, Y2MAX, Y2MIN);
    tri1.normalizada = tri1.matriz;
    mainWindow.adicionarObjeto(tri1);

    QVector<QPair<double, double>> ret1Pontos = { {100, 400}, {400, 400}};
    Matriz ret1(ret1Pontos, "Linha");
    //ret1.normalizada = ret1.normalizar(ret1.matriz, window, X2MAX, X2MIN, Y2MAX, Y2MIN);
    ret1.normalizada = ret1.matriz;


    mainWindow.adicionarObjeto(ret1);

    mainWindow.setWindowTitle("Computação Gráfica");
    mainWindow.atualizarDisplayMatriz();
    mainWindow.atualizarDisplayNormalizada();
    mainWindow.show();
    mainWindow.resize(700,700);

    return app.exec();
}
