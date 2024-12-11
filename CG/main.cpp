#include <QApplication>
#include "mainwindow.h"
#include "matriz.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    // Inicializando pontos diretamente como pares
    QVector<Ponto3D> pontos = {{100, 100}, {300, 100}, {300, 300}, {100, 300}};
    Matriz window(pontos, "Window");
    mainWindow.adicionarObjeto(window);

    pontos = {{50, 50}, {550, 50}, {550, 550}, {50, 550}};
    Matriz viewPort(pontos, "Viewport");
    mainWindow.adicionarObjeto(viewPort);

    // Definindo os pontos da pirâmide
    pontos = {
        {100, 100, 100}, // Vértice base 0
        {150, 100, 100}, // Vértice base 1
        {150, 100, 150}, // Vértice base 2
        {100, 100, 150}, // Vértice base 3
        {125, 150, 125}  // Vértice do topo
    };

    // Definindo as arestas (conectando os pontos)
    QVector<Aresta> arestas = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // Base da pirâmide
        {0, 4}, {1, 4}, {2, 4}, {3, 4}  // Conectando o topo com os vértices da base
    };

    // Definindo as faces (índices dos pontos que formam as faces)

    QVector<Face> faces = {
        Face({0, 1, 4}),  // Face 1 (triângulo)
        Face({1, 2, 4}),  // Face 2 (triângulo)
        Face({2, 3, 4}),  // Face 3 (triângulo)
        Face({3, 0, 4}),  // Face 4 (triângulo)
        Face({0, 1, 2, 3}) // Base (quadrado)
    };

    // Criando uma pirâmide completa (com arestas e faces)
    Matriz piramide(pontos, arestas, faces, "Ambos");
    mainWindow.adicionarObjeto(piramide);

    // Criando uma pirâmide apenas com arestas
    Matriz piramideApenasArestas(pontos, arestas, "Arestas"); // Sem faces
    mainWindow.adicionarObjeto(piramideApenasArestas);

    // Criando uma pirâmide apenas com faces
    Matriz piramideApenasFaces(pontos, faces, "Faces"); // Sem arestas
    mainWindow.adicionarObjeto(piramideApenasFaces);

    // Criando uma pirâmide apenas com pontos (nem arestas nem faces)
    Matriz piramideApenasPontos(pontos, "Pontos");
    mainWindow.adicionarObjeto(piramideApenasPontos);

    mainWindow.setWindowTitle("Computação Gráfica");
    mainWindow.resize(600, 600);

    return app.exec();
}
