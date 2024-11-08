#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>
#include <QPainter>
#include "Matriz.h"
#include "Delay.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void adicionarObjeto(const Matriz& novoObjeto);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onButtonClicked1();
    void onButtonClicked2();
    void onButtonClicked3();
    void seletor(int index);

private:
    Ui::MainWindow *ui;
    QVector<Matriz> objetos;  // Vetor para armazenar cada objeto como uma única instância de Matriz
    void Desenhar(QPainter &painter);

    // Adicione os botões e o menu aqui, agora dentro da MainWindow
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    QComboBox *menu;
};

#endif // MAINWINDOW_H
