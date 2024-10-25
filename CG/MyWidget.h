#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QVector>
#include "Pontos.h"

class MyWidget : public QWidget {
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr);
    void setObjetos(const QVector<Pontos> &objetos); // Método para definir os pontos a serem desenhados

protected:
    void paintEvent(QPaintEvent *event) override; // Método de evento de pintura

private:
    void Desenhar(QPainter &painter); // Método para desenhar
    QVector<Pontos> objetos; // Armazena os pontos
};

#endif // MYWIDGET_H
