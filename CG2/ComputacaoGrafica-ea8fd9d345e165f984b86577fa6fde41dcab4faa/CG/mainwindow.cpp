#include "mainwindow.h"
#include "ui_mainwindow.h"

int atual=0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    matrizDisplay = new QTextEdit(this);
    matrizDisplay->setReadOnly(true);

    // Inicialize os botões e o menu na janela principal
    button1 = new QPushButton("Rotacionar", this);
    button2 = new QPushButton("Transladar", this);
    button3 = new QPushButton("Escalonar", this);
    menu = new QComboBox(this);

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

void MainWindow::adicionarObjeto(const Matriz& novoObjeto, const QString& nome) {
    displayFile.adicionarObjeto(novoObjeto);
    objetos = displayFile.getObjetos();
    menu->addItem(nome);
    qDebug() << "Objeto adicionado:";
    for (const auto& linha : novoObjeto.matriz) {
        QString linhaTexto;
        for (double valor : linha) {
            linhaTexto += QString::number(valor) + " ";
        }
        qDebug() << linhaTexto;
    }
    qDebug() << "Total de objetos:" << objetos.size();
    if (atual == -1) {
        atual = 0;
    }
    update();
}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    Desenhar(painter);
}

void MainWindow::Desenhar(QPainter &painter) {
    for (int i = 0; i < displayFile.tamanho(); ++i) {
        const Matriz& objeto = displayFile.getObjeto(i);
        int numPontos = objeto.matriz[0].size();

        for (int j = 0; j < numPontos; ++j) {
            int k = (j + 1) % numPontos;

            double x1 = objeto.matriz[0][j];
            double y1 = objeto.matriz[1][j];
            double x2 = objeto.matriz[0][k];
            double y2 = objeto.matriz[1][k];

            painter.drawLine(QPointF(x1, y1), QPointF(x2, y2));
        }
    }
}

void MainWindow::atualizarDisplayMatriz() {
    if (atual < 0 || atual >= objetos.size()) return;

    QString matrizTexto;
    const Matriz& objetoAtual = objetos[atual];

    // Exibindo o nome do objeto
    matrizTexto += "Objeto: " + menu->currentText() + "\n";

    // Exibindo o número de pontos (colunas da matriz)
    int numPontos = objetoAtual.matriz[0].size();
    matrizTexto += "Número de pontos: " + QString::number(numPontos) + "\n";

    // Exibindo os valores da matriz
    for (int i = 0; i < objetoAtual.matriz.size(); ++i) {
        matrizTexto += "Linha " + QString::number(i+1) + ": ";
        for (int j = 0; j < objetoAtual.matriz[i].size(); ++j) {
            matrizTexto += QString::number(objetoAtual.matriz[i][j], 'f', 0) + " ";        }
        matrizTexto += "\n";
    }

    matrizDisplay->setText(matrizTexto);
}

void MainWindow::onButtonClicked1() {
    if (atual < 0 || atual >= objetos.size()) {
        qDebug() << "Índice inválido para rotação.";
        return;
    }
    for (int i = 0; i < 10; i++) {
        rotacionar(objetos[atual], 0.0785398); // Realiza a rotação
        displayFile.setObjeto(atual, objetos[atual]); // Atualiza no displayFile
         atualizarDisplayMatriz();
        delay(10);
        update(); // Redesenha a interface
    }
}

void MainWindow::onButtonClicked2() {
    for(int i = 0; i < 10; i++) {
        transladar(objetos[atual], 1, 1);
        displayFile.setObjeto(atual, objetos[atual]); // Atualiza no displayFile
         atualizarDisplayMatriz();
        delay(10);
        update();
    }
}

void MainWindow::onButtonClicked3() {
    for(int i = 0; i < 10; i++) {
        escalonar(objetos[atual], 1.04, 1.04);
        displayFile.setObjeto(atual, objetos[atual]); // Atualiza no displayFile
         atualizarDisplayMatriz();
        delay(10);
        update();
    }
}

void MainWindow::seletor(int index) {
    if (index >= 0 && index < displayFile.tamanho()) {
        atual = index;
        atualizarDisplayMatriz();
    } else {
        qDebug() << "Índice inválido selecionado!";
    }
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);

    // Ajuste o tamanho e posição do matrizDisplay
   // int larguraJanela = this->width();
    int alturaJanela = this->height();
    int larguraMatrizDisplay = 200; // Largura fixa
    int alturaMatrizDisplay = 100; // Altura fixa

    matrizDisplay->setGeometry(10, alturaJanela - alturaMatrizDisplay - 10,
     larguraMatrizDisplay, alturaMatrizDisplay);
}
