#include <QApplication>
#include "mainwindow.h"
#include "matriz.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    // Inicializando pontos diretamente como pares
    QVector<QPair<double, double>> pontos = {{100, 100}, {300, 100}, {300, 300}, {100, 300}};
    Matriz window(pontos);
    mainWindow.adicionarObjeto(window, "Window");

    pontos = {{50, 50}, {550, 50}, {550, 550}, {50, 550}};
    Matriz viewPort(pontos);
    mainWindow.adicionarObjeto(viewPort, "Viewport");

    // Ajustando o barco para estar dentro da window
    pontos = {
        {150, 150}, {130, 150}, {150, 180}, // Triângulo do barco
        {150, 140}, {120, 140}, {130, 130}, {180, 130}, {190, 140}, {150, 140} // Base do barco
    };
    Matriz barco(pontos);
    mainWindow.adicionarObjeto(barco, "Barco");

    pontos = {
        {210, 310}, {260, 260}, {285, 260}, {285, 310}, {285, 260}, {310, 260}, {360, 310},
        {310, 260}, {310, 235}, {360, 235}, {310, 235}, {310, 210}, {360, 160}, {310, 210},
        {285, 210}, {285, 160}, {285, 210}, {260, 210}, {210, 160}, {260, 210}, {260, 235},
        {210, 235}, {260, 235}, {260, 260}
    };
    Matriz sol(pontos);
    mainWindow.adicionarObjeto(sol, "Sol");

    mainWindow.setWindowTitle("Computação Gráfica");
    mainWindow.resize(600, 600);

    return app.exec();
}
