#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>
#include <QPainter>
#include <QTextEdit>
#include <QFrame> // Adiciona o QFrame para delimitar a área de desenho
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
    void atualizarDisplayMatriz(); // Atualiza o display com a matriz do objeto
    void atualizarDisplayNormalizada();
    void fazerSCN();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onButtonClicked1();
    void onButtonClicked2();
    void onButtonClicked3();
    void onButtonClicked4();
    void seletor(int index);
    void normalizarTodos();

private:
    Ui::MainWindow *ui;
    QVector<Matriz> objetos; // Vetor para armazenar cada objeto como uma única instância de Matriz
    void Desenhar(QPainter &painter);

    // Novo componente de frame para a área de desenho
    QFrame *drawingFrame;

    // Botões e menu
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    QPushButton *button4;
    QComboBox *menu;

    // Display para exibir a matriz do objeto selecionado
    QTextEdit *matrizDisplay;
    QTextEdit *normalizadaDisplay;
};

#endif // MAINWINDOW_H
