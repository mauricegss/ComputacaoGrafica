#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Matriz.h"

int atual;
int XMAX = 610; //coordenadas viewport
int XMIN = 50;
int YMAX = 610;
int YMIN = 50;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Frame de desenho
    drawingFrame = new QFrame(this);
    drawingFrame->setGeometry(XMIN, YMIN, XMAX, YMAX); // Define a posição e o tamanho da área de desenho
    drawingFrame->setFrameShape(QFrame::Box);     // Adiciona uma borda para indicar a área de desenho

    // Display .matriz
    matrizDisplay = new QTextEdit(this);
    matrizDisplay->setReadOnly(true);
    matrizDisplay->setGeometry(10, 10, 200, 75);  // Posição e tamanho do campo de texto

    // Display .normalizada
    normalizadaDisplay = new QTextEdit(this);
    normalizadaDisplay->setReadOnly(true);
    normalizadaDisplay->setGeometry(10, 95, 200, 75);  // Posição e tamanho do campo de texto

    // Combo box
    menu = new QComboBox(this);
    menu->setGeometry(220, 10, 100, 30);  // Posição e tamanho da combo box

    // Botões de operações
    button1 = new QPushButton("Rotacionar", this);
    button2 = new QPushButton("Transladar", this);
    button3 = new QPushButton("Escalonar (+)", this);
    button4 = new QPushButton("Escalonar (-)", this);
    button1->setGeometry(330, 10, 80, 30);  // Posição e tamanho do botão Rotacionar
    button2->setGeometry(420, 10, 80, 30);  // Posição e tamanho do botão Transladar
    button3->setGeometry(510, 10, 80, 30);  // Posição e tamanho do botão Escalonar (+)
    button4->setGeometry(600, 10, 80, 30);  // Posição e tamanho do botão Escalonar (-)

    // Conecta os slots e sinais dos botões e combo box
    connect(button1, &QPushButton::clicked, this, &MainWindow::onButtonClicked1);
    connect(button2, &QPushButton::clicked, this, &MainWindow::onButtonClicked2);
    connect(button3, &QPushButton::clicked, this, &MainWindow::onButtonClicked3);
    connect(button4, &QPushButton::clicked, this, &MainWindow::onButtonClicked4);
    connect(menu, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::seletor);

    // Atualiza inicialmente a display da matriz
    atualizarDisplayMatriz();
    atualizarDisplayNormalizada();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::adicionarObjeto(const Matriz& novoObjeto) {
    objetos.append(novoObjeto);  // Adiciona o objeto à lista interna
    menu->addItem(novoObjeto.nome);  // Adiciona o nome do objeto à combo box 'menu'
    fazerSCN();
    update();
}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);

    // Define um recorte de área de desenho para o frame
    painter.setClipRect(drawingFrame->geometry());
    Desenhar(painter);
}

void MainWindow::Desenhar(QPainter &painter) {
    QVector<QVector<double>> objetoAtual;
    for (int l = 0; l < objetos.size(); l++) {
        int numPontos = objetos[l].normalizada[0].size();

        for (int i = 0; i < numPontos; ++i) {
            int j = (i + 1) % numPontos;
            objetoAtual = objetos[l].normalizar(objetos[l].normalizada, objetos[0], XMAX, XMIN, YMAX, YMIN);
            double x1 = objetoAtual[0][i];
            double y1 = objetoAtual[1][i];
            double x2 = objetoAtual[0][j];
            double y2 = objetoAtual[1][j];

            painter.drawLine(QPointF(x1, y1), QPointF(x2, y2));
        }
        //normalizarTodos();
        update();
    }
}

void MainWindow::atualizarDisplayMatriz() {
    if (atual < 0 || atual >= objetos.size()) return;

    QString matrizTexto;
    const Matriz& objetoAtual = objetos[atual];
    for (int i = 0; i < objetoAtual.matriz.size(); ++i) {
        for (int j = 0; j < objetoAtual.matriz[i].size(); ++j) {
            matrizTexto += QString::number(objetoAtual.matriz[i][j]) + " ";
        }
        matrizTexto += "\n";
    }
    matrizDisplay->setText(matrizTexto);
}

void MainWindow::atualizarDisplayNormalizada() {
    if (atual < 0 || atual >= objetos.size()) return;

    QString matrizTexto;
    const Matriz& objetoAtual = objetos[atual];
    for (int i = 0; i < objetoAtual.normalizada.size(); ++i) {
        for (int j = 0; j < objetoAtual.normalizada[i].size(); ++j) {
            matrizTexto += QString::number(objetoAtual.normalizada[i][j]) + " ";
        }
        matrizTexto += "\n";
    }
    normalizadaDisplay->setText(matrizTexto);
}

void MainWindow::onButtonClicked1() {
    if(atual == 0){
        rotacionar(objetos[atual], 45);
        //fazerSCN();
        normalizarTodos();
        update();
        atualizarDisplayMatriz();
        atualizarDisplayNormalizada();
    }
    else{
        for (int i = 0; i < 10; i++) {
            rotacionar(objetos[atual], 4.5);
            delay(10);
            update();
            atualizarDisplayMatriz();
            atualizarDisplayNormalizada();
        }
    }
}

void MainWindow::onButtonClicked2() {
    if(atual == 0){
        transladar(objetos[atual], 10, 10);
        fazerSCN();
        //normalizarTodos();
        update();
        atualizarDisplayMatriz();
        atualizarDisplayNormalizada();
    }
    else{
        for (int i = 0; i < 10; i++) {
            transladar(objetos[atual], 1, 1);
            delay(10);
            update();
            atualizarDisplayMatriz();
            atualizarDisplayNormalizada();
        }
    }
}

void MainWindow::onButtonClicked3() {
    if(atual == 0){
        escalonar(objetos[atual], 0.5, 0.5);
        fazerSCN();
        //normalizarTodos();
        update();
        atualizarDisplayMatriz();
        atualizarDisplayNormalizada();
    }
    else{
        for (int i = 0; i < 10; i++) {
            escalonar(objetos[atual], pow(2, 1.0 / 10.0), pow(2, 1.0 / 10.0));
            delay(10);
            update();
            atualizarDisplayMatriz();
            atualizarDisplayNormalizada();
        }
    }
}

void MainWindow::onButtonClicked4() {
    if(atual == 0){
        escalonar(objetos[atual], 2, 2);
        fazerSCN();
        //normalizarTodos();
        update();
        atualizarDisplayMatriz();
        atualizarDisplayNormalizada();
    }
    else{
        for (int i = 0; i < 10; i++) {
            escalonar(objetos[atual], pow(0.5, 1.0 / 10.0), pow(0.5, 1.0 / 10.0));
            delay(10);
            update();
            atualizarDisplayMatriz();
            atualizarDisplayNormalizada();
        }
    }
}

void MainWindow::seletor(int index) {
    atual = index;
    atualizarDisplayMatriz();
    atualizarDisplayNormalizada();
}

void MainWindow::fazerSCN(){
    centralizarTudo(objetos);
}

void MainWindow::normalizarTodos(){
    objetos[0].matriz = objetos[0].normalizada;
    for(int i = 1; i < objetos.size(); i++){
        objetos[i].normalizada = objetos[i].normalizar(objetos[i].matriz, objetos[0], XMAX, XMIN, YMAX, YMIN);
    }
}
