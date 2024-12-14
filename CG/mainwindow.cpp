#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFrame>

int atual=0;
int XMAX = 550; //coordenadas viewport
int XMIN = 10;
int YMAX = 550;
int YMIN = 10;

/*const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Frame de desenho
    /*viewPort = new QFrame(this);
    viewPort ->setGeometry(XMIN, YMIN, XMAX, YMAX); // Define a posição e o tamanho da área de desenho
    viewPort ->setFrameShape(QFrame::Box); */

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
    button1 = new QPushButton("Escalonar (+)", this);
    button2 = new QPushButton("Escalonar (-)", this);
    button3 = new QPushButton("Transladar", this);
    button4 = new QPushButton("Rotacionar (X)", this);
    button5 = new QPushButton("Rotacionar (Y)", this);
    button6 = new QPushButton("Rotacionar (Z)", this);
    menu = new QComboBox(this);

    // Configure as posições dos botões e do menu
    menu->setGeometry(QRect(QPoint(560, 10), QSize(100, 30)));
    button1->setGeometry(QRect(QPoint(560, 50), QSize(100, 30)));
    button2->setGeometry(QRect(QPoint(560, 90), QSize(100, 30)));
    button3->setGeometry(QRect(QPoint(560, 130), QSize(100, 30)));
    button4->setGeometry(QRect(QPoint(560, 170), QSize(100, 30)));
    button5->setGeometry(QRect(QPoint(560, 210), QSize(100, 30)));
    button6->setGeometry(QRect(QPoint(560, 250), QSize(100, 30)));

    // Conecte os sinais dos botões aos slots correspondentes
    connect(button1, &QPushButton::clicked, this, &MainWindow::onButtonClicked1);
    connect(button2, &QPushButton::clicked, this, &MainWindow::onButtonClicked2);
    connect(button3, &QPushButton::clicked, this, &MainWindow::onButtonClicked3);
    connect(button4, &QPushButton::clicked, this, &MainWindow::onButtonClicked4);
    connect(button5, &QPushButton::clicked, this, &MainWindow::onButtonClicked5);
    connect(button6, &QPushButton::clicked, this, &MainWindow::onButtonClicked6);
    connect(menu, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::seletor);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::adicionarObjeto(const Matriz& novoObjeto) {

    objetos.adicionarObjeto(novoObjeto);
    //displayFile.adicionarObjeto(novoObjeto);
    //objetos = displayFile.getObjetos();

    menu->addItem(novoObjeto.nome);

    update();
}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    aplicarSCN();
    Desenhar(painter);
}

// Define as regiões de código para o Cohen-Sutherland
enum RegionCode {
    INSIDE = 0,  // 0000
    LEFT = 1,    // 0001
    RIGHT = 2,   // 0010
    BOTTOM = 4,  // 0100
    TOP = 8      // 1000
};

// Função para calcular a região de código para um ponto
int calcularCodigo(double x, double y) {
    int code = INSIDE;

    if (x < XMIN) code |= LEFT;
    else if (x > XMAX) code |= RIGHT;

    if (y < YMIN) code |= BOTTOM;
    else if (y > YMAX) code |= TOP;

    return code;
}

// Função de clipping usando Cohen-Sutherland
bool clipping(double &x1, double &y1, double &x2, double &y2) {
    int code1 = calcularCodigo(x1, y1);
    int code2 = calcularCodigo(x2, y2);
    bool accept = false;

    while (true) {
        if ((code1 == 0) && (code2 == 0)) {
            // Ambos os pontos estão dentro da janela
            accept = true;
            break;
        } else if (code1 & code2) {
            // Ambos os pontos estão fora, na mesma região
            break;
        } else {
            // Pelo menos um ponto está fora; calcule o ponto de interseção
            int codeOut = code1 ? code1 : code2;
            double x, y;

            if (codeOut & TOP) { // Acima da janela
                x = x1 + (x2 - x1) * (YMAX - y1) / (y2 - y1);
                y = YMAX;
            } else if (codeOut & BOTTOM) { // Abaixo da janela
                x = x1 + (x2 - x1) * (YMIN - y1) / (y2 - y1);
                y = YMIN;
            } else if (codeOut & RIGHT) { // À direita da janela
                y = y1 + (y2 - y1) * (XMAX - x1) / (x2 - x1);
                x = XMAX;
            } else if (codeOut & LEFT) { // À esquerda da janela
                y = y1 + (y2 - y1) * (XMIN - x1) / (x2 - x1);
                x = XMIN;
            }

            // Substitua o ponto fora pela interseção
            if (codeOut == code1) {
                x1 = x;
                y1 = y;
                code1 = calcularCodigo(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                code2 = calcularCodigo(x2, y2);
            }
        }
    }
    return accept;
}

void MainWindow::Desenhar(QPainter &painter) {
    double x1, y1, x2, y2;
    QVector<QVector<double>> temp;
    temp.resize(4);

    // AQUI A PARTE DE DESENHAR A WINDOW
    int numPontos = objetos[1].matriz[0].size();
    if (numPontos >= 2) { // Garantir que há pelo menos dois pontos
        painter.setPen(Qt::black); // Cor azul para objetos[1]
        for (int j = 0; j < numPontos; ++j) {
            int k = (j + 1) % numPontos; // Liga o último ponto ao primeiro

            x1 = objetos[1].matriz[0][j];
            y1 = objetos[1].matriz[1][j];
            x2 = objetos[1].matriz[0][k];
            y2 = objetos[1].matriz[1][k];

            painter.drawLine(QPointF(x1, y1), QPointF(x2, y2));
        }
    }
    // AQUI

    // Agora desenha os objetos (arestas e faces)
    for (int i = 2; i < objetos.size(); ++i) {
        temp = normalizar(objetos[i].clone, objetos[0].clone, objetos[1].matriz);

        // Desenhando as faces, se existirem
        /*if (!objetos[i].faces.isEmpty()) {
            painter.setPen(Qt::transparent);
            painter.setBrush(Qt::green); // Cor para faces

            // Desenhando as faces
            for (const Face &face : objetos[i].faces) {
                QVector<QPointF> pontosFace;

                for (int idx : face.indices) {
                    double x = temp[0][idx];
                    double y = temp[1][idx];
                    pontosFace.append(QPointF(x, y));
                }

                // Aplica o clipping de polígono
                if (clipPolygon(pontosFace)) {
                    // Desenha a face como um polígono
                    painter.drawPolygon(pontosFace);
                }
            }
        }*/

        // Desenhando as arestas, se existirem (APÓS as faces para sobrepor)
        if (!objetos[i].arestas.isEmpty()) {

            painter.setPen(Qt::blue); // Cor para as arestas

            // Desenhando as arestas

            for (const Aresta &aresta : objetos[i].arestas) {
                int p1 = aresta.p1;
                int p2 = aresta.p2;

                x1 = temp[0][p1];
                y1 = temp[1][p1];
                x2 = temp[0][p2];
                y2 = temp[1][p2];
                // Aplica o algoritmo de Cohen-Sutherland (se necessário)
                if (clipping(x1, y1, x2, y2)) {
                    painter.drawLine(QPointF(x1, y1), QPointF(x2, y2));
                }
            }
        }
        painter.setPen(Qt::red);
        painter.setBrush(Qt::transparent);
        for (int j = 0; j < objetos[i].matriz[0].size(); ++j) {
            double x = temp[0][j];
            double y = temp[1][j];

            // Desenhando o ponto como um pequeno círculo
            /*if(x <= XMAX && x >= XMIN && y <= YMAX && y >= YMIN){
                painter.drawEllipse(QPointF(x, y), 3, 3); // Tamanho do ponto pode ser ajustado (3, 3)
            }*/
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
    infoTexto += "Número de Vértices: " + QString::number(objetoAtual.matriz[0].size()) + "\n";
    infoTexto += "Número de Arestas: " + QString::number(objetoAtual.arestas.size()) + "\n";
    infoTexto += "Número de Faces: " + QString::number(objetoAtual.faces.size()) + "\n";

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
    for(int i = 0; i < 10; i++) {
        escalonar(objetos[atual], 1.05, 1.05, 1.05);
        objetos.setObjeto(atual, objetos[atual]);
        //displayFile.setObjeto(atual, objetos[atual]); // Atualiza no displayFile
        delay(10);
        update();
        atualizarDisplayMatriz();
    }
}

void MainWindow::onButtonClicked2() {
    for(int i = 0; i < 10; i++) {
        escalonar(objetos[atual], 0.95,0.95,0.95);
        objetos.setObjeto(atual, objetos[atual]);
        //displayFile.setObjeto(atual, objetos[atual]); // Atualiza no displayFile
        delay(10);
        update();
        atualizarDisplayMatriz();
    }
}

void MainWindow::onButtonClicked3() {
    for(int i = 0; i < 10; i++) {
        transladar(objetos[atual], -1, -1, 0);
        objetos.setObjeto(atual, objetos[atual]);
        //displayFile.setObjeto(atual, objetos[atual]); // Atualiza no displayFile
        //atualizarDisplayMatriz();
        delay(10);
        update();
        atualizarDisplayMatriz();
    }
}

void MainWindow::onButtonClicked4() {
    if (atual < 0 || atual >= objetos.size()) {
        qDebug() << "Índice inválido para rotação.";
        return;
    }
    for (int i = 0; i < 10; i++) {
        rotacionar(objetos[atual], 4.5, 'x'); // Realiza a rotação
        objetos.setObjeto(atual, objetos[atual]);
        //displayFile.setObjeto(atual, objetos[atual]); // Atualiza no displayFile
        delay(10);
        update(); // Redesenha a interface
        atualizarDisplayMatriz();
    }
}

void MainWindow::onButtonClicked5() {
    if (atual < 0 || atual >= objetos.size()) {
        qDebug() << "Índice inválido para rotação.";
        return;
    }
    for (int i = 0; i < 10; i++) {
        rotacionar(objetos[atual], 4.5, 'y'); // Realiza a rotação
        objetos.setObjeto(atual, objetos[atual]);
        //displayFile.setObjeto(atual, objetos[atual]); // Atualiza no displayFile
        delay(10);
        update(); // Redesenha a interface
        atualizarDisplayMatriz();
    }
}

void MainWindow::onButtonClicked6() {
    if (atual < 0 || atual >= objetos.size()) {
        qDebug() << "Índice inválido para rotação.";
        return;
    }
    for (int i = 0; i < 10; i++) {
        rotacionar(objetos[atual], 4.5, 'z'); // Realiza a rotação
        objetos.setObjeto(atual, objetos[atual]);
        //displayFile.setObjeto(atual, objetos[atual]); // Atualiza no displayFile
        delay(10);
        update(); // Redesenha a interface
        atualizarDisplayMatriz();
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
    double cx = 0, cy = 0, cz =0;
    int numPontos = objetos[0].matriz[0].size();
    for (int i = 0; i < numPontos; ++i) {
        cx += objetos[0].matriz[0][i];
        cy += objetos[0].matriz[1][i];
        cz += objetos[0].matriz[2][i];
    }
    cx /= numPontos;
    cy /= numPontos;
    cz /= numPontos;

    // Transalação
    for(int i = 0; i<objetos.size(); i++){
        transladarClone(objetos[i], -cx, -cy, -cz);
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
}

bool MainWindow::clipPolygon(QVector<QPointF>& pontos) {
    QVector<QPointF> clipped;
    QPointF s;
    // Clipping em cada borda da janela de visualização (esquerda, direita, cima e baixo)
    for (int i = 0; i < 4; ++i) {
        QVector<QPointF> newPoints;
        if (pontos.isEmpty()) {
            return false; // Polígono completamente eliminado
        } else {
            s = pontos.last();
        }
        for (int j = 0; j < pontos.size(); ++j) {
            QPointF p = pontos[j];
            if (i == 0) { // Clipping pela borda esquerda
                if (p.x() >= XMIN) {
                    if (s.x() < XMIN) {
                        double y = s.y() + (p.y() - s.y()) * (XMIN - s.x()) / (p.x() - s.x());
                        newPoints.append(QPointF(XMIN, y));
                    }
                    newPoints.append(p);
                }
                else if (s.x() >= XMIN) {
                    double y = s.y() + (p.y() - s.y()) * (XMIN - s.x()) / (p.x() - s.x());
                    newPoints.append(QPointF(XMIN, y));
                }
            } else if (i == 1) { // Clipping pela borda direita
                if (p.x() <= XMAX) {
                    if (s.x() > XMAX) {
                        double y = s.y() + (p.y() - s.y()) * (XMAX - s.x()) / (p.x() - s.x());
                        newPoints.append(QPointF(XMAX, y));
                    }
                    newPoints.append(p);
                }
                else if (s.x() <= XMAX) {
                    double y = s.y() + (p.y() - s.y()) * (XMAX - s.x()) / (p.x() - s.x());
                    newPoints.append(QPointF(XMAX, y));
                }
            } else if (i == 2) { // Clipping pela borda inferior
                if (p.y() >= YMIN) {
                    if (s.y() < YMIN) {
                        double x = s.x() + (p.x() - s.x()) * (YMIN - s.y()) / (p.y() - s.y());
                        newPoints.append(QPointF(x, YMIN));
                    }
                    newPoints.append(p);
                }
                else if (s.y() >= YMIN) {
                    double x = s.x() + (p.x() - s.x()) * (YMIN - s.y()) / (p.y() - s.y());
                    newPoints.append(QPointF(x, YMIN));
                }
            } else { // Clipping pela borda superior
                if (p.y() <= YMAX) {
                    if (s.y() > YMAX) {
                        double x = s.x() + (p.x() - s.x()) * (YMAX - s.y()) / (p.y() - s.y());
                        newPoints.append(QPointF(x, YMAX));
                    }
                    newPoints.append(p);
                }
                else if (s.y() <= YMAX) {
                    double x = s.x() + (p.x() - s.x()) * (YMAX - s.y()) / (p.y() - s.y());
                    newPoints.append(QPointF(x, YMAX));
                }
            }
            s = p;
        }
        pontos = newPoints;
    }
    return !pontos.isEmpty();
}



