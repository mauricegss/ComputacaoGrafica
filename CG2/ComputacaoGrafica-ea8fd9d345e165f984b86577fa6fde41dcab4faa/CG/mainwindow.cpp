#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFrame>

int atual=0;
int XMAX = 550; //coordenadas viewport
int XMIN = 50;
int YMAX = 550;
int YMIN = 50;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Frame de desenho
    viewPort = new QFrame(this);
    viewPort ->setGeometry(XMIN, YMIN, XMAX, YMAX); // Define a posição e o tamanho da área de desenho
    viewPort ->setFrameShape(QFrame::Box);     // Adiciona uma borda para indicar a área de desenho


    //int larguraJanela = this->width();  // Largura total da janela
    // Display .matriz
    matrizDisplay = new QTextEdit(this);
    matrizDisplay->setReadOnly(true);

    // Display .normalizada
    cloneDisplay = new QTextEdit(this);
    cloneDisplay->setReadOnly(true);
    infoDisplay = new QTextEdit(this);
    infoDisplay->setReadOnly(true);

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

    objetos.adicionarObjeto(novoObjeto);
    //displayFile.adicionarObjeto(novoObjeto);
    //objetos = displayFile.getObjetos();

    menu->addItem(nome);

    update();
}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    aplicarSCN();
    Desenhar(painter);
}

void MainWindow::Desenhar(QPainter &painter) {
    painter.translate(100,100);
    double x1;
    double y1;
    double x2;
    double y2;
    QVector<QVector<double>> temp;
    temp.resize(3);
    for (int i = 0; i < objetos.size(); ++i) {
        //Matriz& objeto = displayFile.getObjeto(i);
        //int numPontos = objeto.matriz[0].size();
        int numPontos = objetos[i].matriz[0].size();

        for (int j = 0; j < numPontos; ++j) {
            int k = (j + 1) % numPontos;
            for (int w = 0; w < 3; ++w) {
                temp[w].resize(numPontos);
            }
            //=======================================================================================================
            //a transformada de viewport ocorre aqui, fazer o clipping antes
            temp = normalizar(objetos[i].clone, objetos[0].clone, XMAX, XMIN, YMAX, YMIN);
            if (temp.size() < 2 || temp[0].size() != numPontos || temp[1].size() != numPontos) {
                qDebug() << "Erro: retorno inesperado de normalizar()!";
                continue;
            }
            /*painter.setPen(Qt::black);
            double x1 = objetos[i].matriz[0][j];
            double y1 = objetos[i].matriz[1][j];
            double x2 = objetos[i].matriz[0][k];
            double y2 = objetos[i].matriz[1][k];

            painter.drawLine(QPointF(x1, y1), QPointF(x2, y2));
            */
            painter.setPen(Qt::red);
            x1 = temp[0][j];
            y1 = temp[1][j];
            x2 = temp[0][k];
            y2 = temp[1][k];
            painter.drawLine(QPointF(x1, y1), QPointF(x2, y2));

        }
    }
}

void MainWindow::atualizarDisplayMatriz() {
    if (atual < 0 || atual >= objetos.size()) return;

    QString matrizTexto, cloneTexto, infoTexto;
    const Matriz& objetoAtual = objetos[atual];

    // Exibindo o nome do objeto
    infoTexto += "Objeto: " + menu->currentText() + "\n";

    // Exibindo o número de pontos (colunas da matriz)
    infoTexto += "Número de pontos: " + QString::number(objetoAtual.matriz[0].size()) + "\n";

    // Exibindo os valores da matriz
    infoTexto += "View Up: (" + QString::number(objetos[0].vUp.first) + ", "+ QString::number(objetos[0].vUp.second) + ")\n";
    for (int i = 0; i < objetoAtual.matriz.size(); ++i) {
        for (int j = 0; j < objetoAtual.matriz[i].size(); ++j) {
            matrizTexto += QString::number(objetoAtual.matriz[i][j], 'f', 0) + " ";
            cloneTexto += QString::number(objetoAtual.clone[i][j], 'f', 0) + " ";
        }
        matrizTexto += "\n";
        cloneTexto += "\n";
    }

    infoDisplay->setText(infoTexto);
    matrizDisplay->setText(matrizTexto);
    cloneDisplay->setText(cloneTexto);
}

void MainWindow::onButtonClicked1() {
    if (atual < 0 || atual >= objetos.size()) {
        qDebug() << "Índice inválido para rotação.";
        return;
    }
    for (int i = 0; i < 10; i++) {
        rotacionar(objetos[atual], 4.5); // Realiza a rotação
        objetos.setObjeto(atual, objetos[atual]);
        //displayFile.setObjeto(atual, objetos[atual]); // Atualiza no displayFile
        atualizarDisplayMatriz();
        delay(10);
        update(); // Redesenha a interface
    }
}

void MainWindow::onButtonClicked2() {
    for(int i = 0; i < 10; i++) {
        transladar(objetos[atual], 1, 1);
        objetos.setObjeto(atual, objetos[atual]);
        //displayFile.setObjeto(atual, objetos[atual]); // Atualiza no displayFile
        delay(10);
        update();
    }
}

void MainWindow::onButtonClicked3() {
    for(int i = 0; i < 10; i++) {
        escalonar(objetos[atual], 1.04, 1.04);
        objetos.setObjeto(atual, objetos[atual]);
        //displayFile.setObjeto(atual, objetos[atual]); // Atualiza no displayFile
        atualizarDisplayMatriz();
        delay(10);
        update();
    }
}

void MainWindow::seletor(int index) {
    if (index >= 0 && index < objetos.size()) {
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
    int larguraDisplay = 200; // Largura fixa
    int alturaDisplay = 100; // Altura fixa

    infoDisplay->setGeometry(10, alturaJanela - alturaDisplay - 10, larguraDisplay, alturaDisplay);
    matrizDisplay->setGeometry(10 + larguraDisplay + 10, alturaJanela - alturaDisplay - 10, larguraDisplay, alturaDisplay);
    cloneDisplay->setGeometry(10 + 2 * larguraDisplay + 20, alturaJanela - alturaDisplay - 10, larguraDisplay, alturaDisplay);
}

void MainWindow::aplicarSCN(){

    // Passo 0 - Criar Clone = Matriz
    for(int i = 0; i<objetos.size(); i++){
        objetos[i].clone = objetos[i].matriz;
    }

    // Passo 1 - Translade Wc para a origem e o mundo de -Wcx e -Wcy

    // Calcula o centro geométrico da Window
    double cx = 0, cy = 0;
    int numPontos = objetos[0].matriz[0].size();
    for (int i = 0; i < numPontos; ++i) {
        cx += objetos[0].matriz[0][i];
        cy += objetos[0].matriz[1][i];
    }
    cx /= numPontos;
    cy /= numPontos;

    // Transalação
    for(int i = 0; i<objetos.size(); i++){
        transladarClone(objetos[i], -cx, -cy);
    }

    // Passo 2 - Determine vUp e o angulo vUp com Y
    double vx = objetos[0].vUp.first;
    double vy = objetos[0].vUp.second;

    double moduloV = qSqrt(vx * vx + vy * vy);
    double theta = qAcos(vy / moduloV);

    if (vx < 0) {
        theta = -theta;
    }

    // Passo 3 - Rotacione o mundo por -theta
    rotacionarClone(objetos[0], objetos[0], qRadiansToDegrees(theta));
    for (int i = 1; i < objetos.size(); ++i) {
        rotacionarClone(objetos[0],objetos[i], -qRadiansToDegrees(theta)); // Converta θ para graus e aplique a rotação
    }

    //

}
