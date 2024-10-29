#include "MyWidget.h"
#include "Delay.h"
#include <QPushButton>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent) {
    QPushButton *button1 = new QPushButton("Rotacionar", this);
    QPushButton *button2 = new QPushButton("Transladar", this);
    QPushButton *button3 = new QPushButton("Escalonar", this);

    button1->setGeometry(QRect(QPoint(10, 10), QSize(100, 30)));
    button2->setGeometry(QRect(QPoint(120, 10), QSize(100, 30)));
    button3->setGeometry(QRect(QPoint(230, 10), QSize(100, 30)));

    connect(button1, &QPushButton::clicked, this, &MyWidget::onButtonClicked1);
    connect(button2, &QPushButton::clicked, this, &MyWidget::onButtonClicked2);
    connect(button3, &QPushButton::clicked, this, &MyWidget::onButtonClicked3);
}

void MyWidget::adicionarObjeto(const QVector<Pontos> &novosObjetos) {
    this->objetos.append(novosObjetos);
    update();
}

void MyWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    Desenhar(painter);
}

void MyWidget::Desenhar(QPainter &painter) {
    for (const QVector<Pontos>& poligono : objetos) {
        if (poligono.size() == 1) {
            painter.drawPoint(poligono[0].x, poligono[0].y);
        } else {
            for (int i = 0; i < poligono.size() - 1; i++) {
                painter.drawLine(poligono[i].x, poligono[i].y, poligono[i + 1].x, poligono[i + 1].y);
            }
            if (poligono.size() >= 3) {
                painter.drawLine(poligono.last().x, poligono.last().y, poligono.first().x, poligono.first().y);
            }

        }
    }
}

void MyWidget::onButtonClicked1() {
    for(int i=0; i<10;i++){
        rotacionar(objetos.last(), 0.0785398);
        delay(10);
        update();
    }
}

void MyWidget::onButtonClicked2() {
    for(int i=0; i<10;i++){
        transladar(objetos.last(), 1, 1);
        delay(10);
        update();
    }
}

void MyWidget::onButtonClicked3() {
    for(int i=0; i<10;i++){
        escalonar(objetos.last(), 1.04, 1.04);
        delay(10);
        update();
    }
}
