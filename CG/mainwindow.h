#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>
#include <QPainter>
#include "matriz.h"
#include "delay.h"
#include "displayfile.h"
#include <QFrame>
#include <QTextEdit>

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
    //void MainWindow::adicionarObjeto(const Matriz& novoObjeto, )


protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onButtonClicked1();
    void onButtonClicked2();
    void onButtonClicked3();
    void onButtonClicked4();
    void onButtonClicked5();
    void onButtonClicked6();
    void seletor(int index);

private:
    Ui::MainWindow *ui;
    //QVector<Matriz> objetos; // Vetor para armazenar cada objeto como uma única instância de Matriz
    DisplayFile objetos;
    void Desenhar(QPainter &painter);
    void aplicarSCN();
    void atualizarDisplayMatriz();
    void resizeEvent(QResizeEvent* event);
    bool clipPolygon(QVector<QPointF>& pontos);

    // Adicione os botões e o menu aqui, agora dentro da MainWindow
    QFrame *viewPort;
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    QPushButton *button4;
    QPushButton *button5;
    QPushButton *button6;
    QComboBox *menu;
    QTextEdit *matrizDisplay;
    QTextEdit *cloneDisplay;
    QTextEdit *infoDisplay;
};

#endif // MAINWINDOW_H
