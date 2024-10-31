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
    int atual = 0;
    QVector<QVector<Matriz>> objetos;
    void rotacionar(Matriz& objeto, double angulo);
    void transladar(Matriz& objeto, double dx, double dy);
    void escalonar(Matriz& objeto, double sx, double sy);
    void Desenhar(QPainter &painter);
};

#endif // MYWIDGET_H
