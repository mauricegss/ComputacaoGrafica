#include "MyWidget.h"
#include <QPainter>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent) {
    // Inicialização, se necessário
}

void MyWidget::setObjetos(const QVector<Pontos> &novosObjetos) {
    this->objetos += novosObjetos; // Adiciona os novos objetos ao vetor existente
    update(); // Solicita atualização para redesenhar todos
}

void MyWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event); // Evita avisos se o parâmetro não for utilizado

    QPainter painter(this); // Inicializa o QPainter com o widget atual
    Desenhar(painter); // Chama a função Desenhar passando o QPainter
}

void MyWidget::Desenhar(QPainter &painter) {

    if (objetos.size() == 1){
        painter.drawPoint(objetos[0].x, objetos[0].y);
    }

    for (int i = 0; i < objetos.size() - 1; ++i) {
        painter.drawLine(objetos[i].x, objetos[i].y, objetos[i + 1].x, objetos[i + 1].y);
    }

    // Fecha o polígono, se houver pelo menos 2 pontos
    if (objetos.size() >= 3) {
        painter.drawLine(objetos.last().x, objetos.last().y, objetos.first().x, objetos.first().y);
    }
}
