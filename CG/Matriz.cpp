#include "Matriz.h"

void transladar(QVector<Pontos>& objeto, double X, double Y) {
    for (int i = 0; i < objeto.size(); i++) { // Corrigido para percorrer todos os pontos
        objeto[i].x += X; // Translada em X
        objeto[i].y += Y; // Translada em Y
    }
}

void escalar(QVector<Pontos>& objeto, double X, double Y){

    double xsave = objeto[0].x;
    double ysave = objeto[0].y;

    transladar(objeto, -xsave, -ysave);

    for(int i=0;i<objeto.size();i++){

        objeto[i].x = objeto[i].x * X;
        objeto[i].y = objeto[i].y * Y;

    }

    transladar(objeto, xsave, ysave);


}

void rotacionar(QVector<Pontos>& objeto, double X){

    double save;
    double xsave = objeto[0].x;
    double ysave = objeto[0].y;

    transladar(objeto, -xsave, -ysave);

    for(int i=0;i<objeto.size();i++){

        save = objeto[i].x;
        objeto[i].x = objeto[i].x*cos(X) - objeto[i].y*sin(X);
        objeto[i].y = save*sin(X) + objeto[i].y*cos(X);

    }

    transladar(objeto, xsave, ysave);
}
