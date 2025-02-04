#include <QApplication>
#include "mainwindow.h"
#include "matriz.h"
#include "leitorobj.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    // Criando o leitor de arquivos OBJ
    OBJFileReader reader;

    // Inicializando pontos para o objeto "Window"
    QVector<Ponto3D> pontos = {{-100, -100, 1}, {100, -100, 1}, {100, 100, 1}, {-100, 100, 1}};
    Matriz window(pontos, "Window");
    mainWindow.adicionarObjeto(window);  // Adicionando objeto à janela principal

    // Inicializando pontos para o objeto "Viewport"
    pontos = {{10, 10}, {550, 10}, {550, 560}, {10, 560}};
    Matriz viewPort(pontos, "Viewport");
    mainWindow.adicionarObjeto(viewPort);  // Adicionando objeto à janela principal
    /*
    // Carregando um objeto externo (arquivo OBJ)
    QString objFilename = "K:/projeto.cg/Arquivosobj/8336/Pokemon XY/Gardevoir/GardevoirMega.obj";
    Matriz Gardevoir = reader.lerMatriz(objFilename, "GardevoirMega");
    mainWindow.adicionarObjeto(Gardevoir);  // Adicionando o objeto externo à janela principal
    */
    QString objFilename2 = "K:/projeto.cg/Arquivosobj/8819/Pokemon XY/Vaporeon/Vaporeon.obj";
    Matriz Vaporeon = reader.lerMatriz(objFilename2, "Vaporeon");
    mainWindow.adicionarObjeto(Vaporeon);  // Adicionando o objeto externo à janela principal

    // Configurações finais da janela principal
    mainWindow.setWindowTitle("Computação Gráfica");
    mainWindow.resize(670, 570);

    // Inicia o loop de execução da aplicação
    return app.exec();
}
