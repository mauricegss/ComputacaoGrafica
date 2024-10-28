#include "Matriz.h"

void centroGeometrico(QVector<Pontos>& objeto, double& xsave, double& ysave){

    double area = 0.0;
    for (int i = 0; i < objeto.size(); i++) {
        int j = (i + 1) % objeto.size();
        double save = objeto[i].x * objeto[j].y - objeto[j].x * objeto[i].y;
        area += save;
        xsave += (objeto[i].x + objeto[j].x) * save;
        ysave += (objeto[i].y + objeto[j].y) * save;
    }
    area *= 0.5;
    xsave /= (6.0 * area);
    ysave /= (6.0 * area);

}

void transladar(QVector<Pontos>& objeto, double X, double Y) {
    for (int i = 0; i < objeto.size(); i++) { // Corrigido para percorrer todos os pontos
        objeto[i].x += X; // Translada em X
        objeto[i].y += Y; // Translada em Y
    }
}

void escalonar(QVector<Pontos>& objeto, double X, double Y) {

    double xsave;
    double ysave;
    centroGeometrico(objeto, xsave, ysave);

    transladar(objeto, -xsave, -ysave);

    for (int i = 0; i < objeto.size(); i++) {
        objeto[i].x *= X;
        objeto[i].y *= Y;
    }

    transladar(objeto, xsave, ysave);

}


void rotacionar(QVector<Pontos>& objeto, double X){

    double save;
    double xsave;
    double ysave;
    centroGeometrico(objeto, xsave, ysave);

    transladar(objeto, -xsave, -ysave);

    for(int i=0;i<objeto.size();i++){
        save = objeto[i].x;
        objeto[i].x = objeto[i].x*cos(X) - objeto[i].y*sin(X);
        objeto[i].y = save*sin(X) + objeto[i].y*cos(X);

    }

    transladar(objeto, xsave, ysave);

}
