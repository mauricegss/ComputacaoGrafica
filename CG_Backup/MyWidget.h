#ifndef MYWIDGET_H // Defina uma macro de inclusão
#define MYWIDGET_H

#include "Matriz.h"
#include <QWidget>
#include <QPainter>

class MyWidget : public QWidget {
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = nullptr);
    void adicionarObjeto(const QVector<Pontos> &novosObjetos); // Adiciona um novo polígono

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<QVector<Pontos>> objetos; // Vetor de polígonos
    void Desenhar(QPainter &painter); // Função para desenhar os objetos
};

#endif // MYWIDGET_H
