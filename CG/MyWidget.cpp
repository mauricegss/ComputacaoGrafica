#include "MyWidget.h"
#include "Delay.h"
#include <QPushButton>
#include <QComboBox>
#include <QPainter>
#include "Matriz.h"

MyWidget::MyWidget(QWidget *parent) : QWidget(parent) {
    QPushButton *button1 = new QPushButton("Rotacionar", this);
    QPushButton *button2 = new QPushButton("Transladar", this);
    QPushButton *button3 = new QPushButton("Escalonar", this);

    QComboBox *menu = new QComboBox(this);
    menu->addItem("Quadrado");
    menu->addItem("Triangulo");
    menu->addItem("Retangulo");

    button1->setGeometry(QRect(QPoint(10, 10), QSize(100, 30)));
    button2->setGeometry(QRect(QPoint(120, 10), QSize(100, 30)));
    button3->setGeometry(QRect(QPoint(230, 10), QSize(100, 30)));
    menu->setGeometry(QRect(QPoint(450, 10), QSize(100, 30)));

    connect(button1, &QPushButton::clicked, this, &MyWidget::onButtonClicked1);
    connect(button2, &QPushButton::clicked, this, &MyWidget::onButtonClicked2);
    connect(button3, &QPushButton::clicked, this, &MyWidget::onButtonClicked3);
    connect(menu, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MyWidget::seletor);
}

void MyWidget::adicionarObjeto(const QVector<Matriz> &novosObjetos) {
    this->objetos.append(novosObjetos);
    update();
}

void MyWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    Desenhar(painter);
}

void MyWidget::Desenhar(QPainter &painter) {
    for (const QVector<Matriz>& poligono : objetos) {
        if (poligono.size() == 1) {
            double x = poligono[0].matrizPonto()[0][0];
            double y = poligono[0].matrizPonto()[1][0];
            painter.drawPoint(x, y);
        } else {
            for (int i = 0; i < poligono.size() - 1; i++) {
                double x1 = poligono[i].matrizPonto()[0][0];
                double y1 = poligono[i].matrizPonto()[1][0];
                double x2 = poligono[i + 1].matrizPonto()[0][0];
                double y2 = poligono[i + 1].matrizPonto()[1][0];
                painter.drawLine(x1, y1, x2, y2);
            }
            if (poligono.size() >= 3) {
                double x_last = poligono.last().matrizPonto()[0][0];
                double y_last = poligono.last().matrizPonto()[1][0];
                double x_first = poligono.first().matrizPonto()[0][0];
                double y_first = poligono.first().matrizPonto()[1][0];
                painter.drawLine(x_last, y_last, x_first, y_first);
            }
        }
    }
}

void MyWidget::rotacionar(Matriz& objeto, double angulo) {
    double cosA = cos(angulo);
    double sinA = sin(angulo);
    objeto.matriz[0][0] = cosA;
    objeto.matriz[0][1] = -sinA;
    objeto.matriz[1][0] = sinA;
    objeto.matriz[1][1] = cosA;
}

void MyWidget::transladar(Matriz& objeto, double dx, double dy) {
    objeto.matrizIdentidadeT(dx, dy);
}

void MyWidget::escalonar(Matriz& objeto, double sx, double sy) {
    objeto.matrizIdentidadeE(sx, sy);
}

void MyWidget::seletor(int index) {
    atual = index;
}

void MyWidget::onButtonClicked1() {
    for(int i = 0; i < 10; i++) {
        rotacionar(objetos[atual][0], 0.0785398);  // Exemplo de rotação de 4.5 graus em radianos
        delay(10);
        update();
    }
}

void MyWidget::onButtonClicked2() {
    for(int i = 0; i < 10; i++) {
        transladar(objetos[atual][0], 1, 1);  // Exemplo de translação
        delay(10);
        update();
    }
}

void MyWidget::onButtonClicked3() {
    for(int i = 0; i < 10; i++) {
        escalonar(objetos[atual][0], 1.04, 1.04);  // Exemplo de escala 1.04x
        delay(10);
        update();
    }
}
