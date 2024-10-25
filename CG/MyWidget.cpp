#include "MyWidget.h"

MyWidget::MyWidget(QWidget *parent) : QWidget(parent) {
    // Inicialização, se necessário
}

void MyWidget::adicionarObjeto(const QVector<Pontos> &novosObjetos) {
    this->objetos.append(novosObjetos); // Adiciona o novo polígono ao vetor de polígonos
    update(); // Solicita atualização para redesenhar
}

void MyWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event); // Evita avisos se o parâmetro não for utilizado

    QPainter painter(this); // Inicializa o QPainter com o widget atual
    Desenhar(painter); // Chama a função Desenhar passando o QPainter
}

void MyWidget::Desenhar(QPainter &painter) {
    for (const QVector<Pontos>& poligono : objetos) {
        if (poligono.size() == 1) {
            painter.drawPoint(poligono[0].x, poligono[0].y);
        } else {
            // Desenha as linhas do polígono
            for (int i = 0; i < poligono.size() - 1; i++) {
                painter.drawLine(poligono[i].x, poligono[i].y, poligono[i + 1].x, poligono[i + 1].y);
            }
            // Fecha o polígono, se houver pelo menos 3 pontos
            if (poligono.size() >= 3) {
                painter.drawLine(poligono.last().x, poligono.last().y, poligono.first().x, poligono.first().y);
            }

        }
    }
}
