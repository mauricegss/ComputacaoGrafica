#ifndef MYWIDGET_H
#define MYWIDGET_H

#include "Matriz.h"
#include <QWidget>
#include <QPainter>
#include "Delay.h"
#include <QPushButton>
#include <QComboBox>

class MyWidget : public QWidget {
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = nullptr);
    void adicionarObjeto(const Matriz& novoObjeto);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onButtonClicked1();
    void onButtonClicked2();
    void onButtonClicked3();
    void seletor(int index);

private:
    QVector<Matriz> objetos;  // Vetor para armazenar cada objeto como uma única instância de Matriz
    void Desenhar(QPainter &painter);
};

#endif // MYWIDGET_H
