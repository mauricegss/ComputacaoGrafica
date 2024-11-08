#include "MyWidget.h"

int atual;

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
    connect(menu,  QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MyWidget::seletor);
}

void MyWidget::adicionarObjeto(const Matriz& novoObjeto) {
    objetos.append(novoObjeto);  // Adiciona o novo objeto ao vetor de objetos
    update();  // Solicita uma atualização da interface para desenhar o novo objeto
}

void MyWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    Desenhar(painter);
}

void MyWidget::Desenhar(QPainter &painter) {
    for (const Matriz& objeto : objetos) {
        int numPontos = objeto.matriz[0].size();  // Número de pontos (colunas) na matriz do objeto

        for (int i = 0; i < numPontos; ++i) {
            int j = (i + 1) % numPontos;  // Conecta o último ponto ao primeiro para fechar o polígono

            double x1 = objeto.matriz[0][i];
            double y1 = objeto.matriz[1][i];
            double x2 = objeto.matriz[0][j];
            double y2 = objeto.matriz[1][j];

            painter.drawLine(QPointF(x1, y1), QPointF(x2, y2));
        }
    }
}

void MyWidget::onButtonClicked1() {
    for(int i = 0; i < 10; i++) {
        rotacionar(objetos[atual], 0.0785398);  // Rotaciona o objeto atual
        delay(10);
        update();
    }
}

void MyWidget::onButtonClicked2() {
    for(int i = 0; i < 10; i++) {
        transladar(objetos[atual], 1, 1);  // Translada o objeto atual
        delay(10);
        update();
    }
}

void MyWidget::onButtonClicked3() {
    for(int i = 0; i < 10; i++) {
        escalonar(objetos[atual], 1.04, 1.04);  // Escalona o objeto atual
        delay(10);
        update();
    }
}

void MyWidget::seletor(int index) {
    if (index >= 0 && index < objetos.size()) {
        atual = index;  // Define o objeto atual com base na seleção
    }
}
