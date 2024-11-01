#include "MyWidget.h"
#include "Delay.h"
#include <QPushButton>
#include <QComboBox>

int atual;

MyWidget::MyWidget(QWidget *parent) : QWidget(parent) {
    QPushButton *button1 = new QPushButton("Rotacionar", this);
    QPushButton *button2 = new QPushButton("Transladar", this);
    QPushButton *button3 = new QPushButton("Escalonar", this);
    //QPushButton *button4 = new QPushButton("Quadrado", this);
    //QPushButton *button5 = new QPushButton("Triangulo", this);
    //QPushButton *button6 = new QPushButton("Retangulo", this);

    QComboBox *menu = new QComboBox(this);
    menu->addItem("Quadrado");
    menu->addItem("Triangulo");
    menu->addItem("Retangulo");

    button1->setGeometry(QRect(QPoint(10, 10), QSize(100, 30)));
    button2->setGeometry(QRect(QPoint(120, 10), QSize(100, 30)));
    button3->setGeometry(QRect(QPoint(230, 10), QSize(100, 30)));
    //button4->setGeometry(QRect(QPoint(340, 10), QSize(100, 30)));
    //button5->setGeometry(QRect(QPoint(450, 10), QSize(100, 30)));
    //button6->setGeometry(QRect(QPoint(560, 10), QSize(100, 30)));
    menu->setGeometry(QRect(QPoint(450, 10), QSize(100, 30)));

    connect(button1, &QPushButton::clicked, this, &MyWidget::onButtonClicked1);
    connect(button2, &QPushButton::clicked, this, &MyWidget::onButtonClicked2);
    connect(button3, &QPushButton::clicked, this, &MyWidget::onButtonClicked3);
    connect(menu,  QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MyWidget::seletor);
    //connect(button4, &QPushButton::clicked, this, &MyWidget::onButtonClicked4);
    //connect(button5, &QPushButton::clicked, this, &MyWidget::onButtonClicked5);
    //connect(button6, &QPushButton::clicked, this, &MyWidget::onButtonClicked6);
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
        rotacionar(objetos[atual], 0.0785398);
        delay(10);
        update();
    }
}

void MyWidget::onButtonClicked2() {
    for(int i=0; i<10;i++){
        transladar(objetos[atual], 1, 1);
        delay(10);
        update();
    }
}

void MyWidget::onButtonClicked3() {
    for(int i=0; i<10;i++){
        escalonar(objetos[atual], 1.04, 1.04);
        delay(10);
        update();
    }
}

void MyWidget::seletor(int index) {
    switch(index){
        case 0:
            atual = 0;
            break;
        case 1:
            atual = 1;
            break;
        case 2:
            atual = 2;
            break;
    }
}

/*void MyWidget::onButtonClicked4() {
    atual = 0;
}

void MyWidget::onButtonClicked5() {
    atual = 1;
}

void MyWidget::onButtonClicked6() {
    atual = 2;
}*/
