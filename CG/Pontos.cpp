#include "Pontos.h"

void Desenhar(QVector<Pontos> objeto) {
    QPainter painter;
    for (int i = 0; i < objeto.size() - 1; ++i) {
        painter.drawLine(objeto[i].x, objeto[i].y, objeto[i + 1].x, objeto[i + 1].y);
    }

    // Fecha o polígono, se houver pelo menos 2 pontos
    if (objeto.size() > 1) {
        painter.drawLine(objeto.last().x, objeto.last().y, objeto.first().x, objeto.first().y);
    }
}
