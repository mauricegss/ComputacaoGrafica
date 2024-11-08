#include "mainwindow.h"
#include "ui_mainwindow.h"

int atual;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Inicialize os botões e o menu na janela principal
    button1 = new QPushButton("Rotacionar", this);
    button2 = new QPushButton("Transladar", this);
    button3 = new QPushButton("Escalonar", this);
    menu = new QComboBox(this);

    // Adicione itens ao menu
    menu->addItem("Quadrado");
    menu->addItem("Triangulo");
    menu->addItem("Retangulo");

    // Configure as posições dos botões e do menu
    button1->setGeometry(QRect(QPoint(10, 10), QSize(100, 30)));
    button2->setGeometry(QRect(QPoint(120, 10), QSize(100, 30)));
    button3->setGeometry(QRect(QPoint(230, 10), QSize(100, 30)));
    menu->setGeometry(QRect(QPoint(450, 10), QSize(100, 30)));

    // Conecte os sinais dos botões aos slots correspondentes
    connect(button1, &QPushButton::clicked, this, &MainWindow::onButtonClicked1);
    connect(button2, &QPushButton::clicked, this, &MainWindow::onButtonClicked2);
    connect(button3, &QPushButton::clicked, this, &MainWindow::onButtonClicked3);
    connect(menu, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::seletor);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::adicionarObjeto(const Matriz& novoObjeto) {
    objetos.append(novoObjeto);
    update();
}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    Desenhar(painter);
}

void MainWindow::Desenhar(QPainter &painter) {
    for (const Matriz& objeto : objetos) {
        int numPontos = objeto.matriz[0].size();

        for (int i = 0; i < numPontos; ++i) {
            int j = (i + 1) % numPontos;

            double x1 = objeto.matriz[0][i];
            double y1 = objeto.matriz[1][i];
            double x2 = objeto.matriz[0][j];
            double y2 = objeto.matriz[1][j];

            painter.drawLine(QPointF(x1, y1), QPointF(x2, y2));
        }
    }
}

void MainWindow::onButtonClicked1() {
    for(int i = 0; i < 10; i++) {
        rotacionar(objetos[atual], 0.0785398);
        delay(10);
        update();
    }
}

void MainWindow::onButtonClicked2() {
    for(int i = 0; i < 10; i++) {
        transladar(objetos[atual], 1, 1);
        delay(10);
        update();
    }
}

void MainWindow::onButtonClicked3() {
    for(int i = 0; i < 10; i++) {
        escalonar(objetos[atual], 1.04, 1.04);
        delay(10);
        update();
    }
}

void MainWindow::seletor(int index) {
    if (index >= 0 && index < objetos.size()) {
        atual = index;
    }
}
