#ifndef MYWIDGET_H
#define MYWIDGET_H

#include "Matriz.h"
#include <QWidget>
#include <QPainter>

class MyWidget : public QWidget {
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = nullptr);
    void adicionarObjeto(const QVector<Matriz> &novosObjetos);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onButtonClicked1();
    void onButtonClicked2();
    void onButtonClicked3();
    //void onButtonClicked4();
    //void onButtonClicked5();
    //void onButtonClicked6();
    void seletor(int index);

private:
    QVector<QVector<Matriz>> objetos;
    void Desenhar(QPainter &painter);
};

#endif // MYWIDGET_H
