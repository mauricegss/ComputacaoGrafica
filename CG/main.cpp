#include <QApplication>
#include "mainwindow.h"
#include "Matriz.h"

QVector<QPair<double, double>> vpPontos = { {0,0}, {600, 0}, {600, 600}, {0, 600} };
Matriz vp(vpPontos, "window");


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;

    // Inicializando pontos diretamente como pares
    vp.normalizada = vp.matriz;
    mainWindow.adicionarObjeto(vp);

    QVector<QPair<double, double>> quad1Pontos = { {100, 100}, {200, 100}, {200, 200}, {100, 200} };
    Matriz quad1(quad1Pontos, "Quadradin");
    quad1.normalizada = quad1.normalizar(quad1.matriz, vp);
    mainWindow.adicionarObjeto(quad1);

    QVector<QPair<double, double>> tri1Pontos = { {300, 100}, {500, 100}, {500, 300} };
    Matriz tri1(tri1Pontos, "Tri Retangulo");
    tri1.normalizada = tri1.normalizar(tri1.matriz, vp);
    mainWindow.adicionarObjeto(tri1);

    QVector<QPair<double, double>> ret1Pontos = { {100, 400}, {400, 400}};
    Matriz ret1(ret1Pontos, "Linha");
    ret1.normalizada = ret1.normalizar(ret1.matriz, vp);
    mainWindow.adicionarObjeto(ret1);

    mainWindow.setWindowTitle("Computação Gráfica");
    mainWindow.atualizarDisplayMatriz();
    mainWindow.atualizarDisplayNormalizada();
    mainWindow.showMaximized();

    return app.exec();
}
