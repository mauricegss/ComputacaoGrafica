#include <QApplication>
#include "MyWidget.h"
#include "Matriz.h"

//QVector<Pontos> *vetorAtual;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MyWidget myWidget;
    myWidget.show();

   /* QVector<Pontos> quad1 = { {100, 100}, {200,100}, {200,200}, {100,200} };
    myWidget.adicionarObjeto(quad1);

    QVector<Pontos> tri1 = { {300, 100}, {500,100}, {500,300}  };
    myWidget.adicionarObjeto(tri1);

    QVector<Pontos> ret1 = { {100, 400}, {400,400}, {400,600}, {100,600} };
    myWidget.adicionarObjeto(ret1);*/

    QVector<Matriz> quad1 = { {100, 100}, {200,100}, {200,200}, {100,200} };
    myWidget.adicionarObjeto(quad1);

    myWidget.setWindowTitle("Computação Gráfica");
    myWidget.resize(1000,800);

    return app.exec();
}
