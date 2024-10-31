#include "Matriz.h"

/*void transladar(QVector<Pontos>& objeto, double dx, double dy){
    Matriz matrizTransformacao;
    QVector<QVector<double>> matriz = matrizTransformacao.matrizIdentidadeT(dx, dy);
    double matrizComposta[3][1];

    //colocar aqui a multipliacao entre a matriz 3x3 de translação x o ponto de origem do objeto EU ACHO

    matrizTransformacao.multiplicarMatrizes(objeto, matrizComposta); // agora, vai multiplicar todos os pontos pela matriz composta para transladar o objeto

}*/

/*void rotacionar(QVector<Pontos>& Objeto) {
    //criar a matriz da rotação declarando direto na função
    double matrizComposta[3][1];

    //colocar aqui a multipliacao entre a matriz 3x3 de translação x o ponto de origem do objeto EU ACHO

    //multiplicarMatrizes(Objeto, matrizComposta);
}*/

void escalonar(QVector<Matriz>& objetos, double sx, double sy) {
    for (Matriz& objeto : objetos) {
        // Obtenha a matriz de ponto do objeto
        QVector<QVector<double>> matriz1 = objeto.matrizPonto();

        // Obtenha a matriz de escala
        QVector<QVector<double>> matriz2 = objeto.matrizIdentidadeE(sx, sy);

        // Crie uma matriz composta para armazenar o resultado
        QVector<QVector<double>> resultado(3, QVector<double>(1, 0));

        // Realize a multiplicação de matrizes
        for (int i = 0; i < 3; ++i) {
            for (int k = 0; k < 3; ++k) {
                resultado[i][0] += matriz2[i][k] * matriz1[k][0];
            }
        }

        objeto.matriz[0][0] = resultado[0][0];
        objeto.matriz[1][0] = resultado[1][0];
        objeto.matriz[2][0] = resultado[2][0];
    }
}
