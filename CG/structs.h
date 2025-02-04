#ifndef STRUCTS_H
#define STRUCTS_H
#include <QVector>

//Estrutura para representar um ponto 3D
struct Ponto3D {
    double x, y, z;

    Ponto3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
};

//Estrutura para representar uma aresta, conectando dois pontos
struct Aresta {
    int p1;  //Índice do primeiro ponto
    int p2;  //Índice do segundo ponto

    Aresta(int p1, int p2) : p1(p1), p2(p2) {}
};

//Estrutura para representar uma face, composta por múltiplos vértices
struct Face {
    QVector<int> indices;  //Índices dos vértices que formam a face

    Face() = default; //Construtor padrão
    Face(std::initializer_list<int> initList) : indices(initList) {}
};

class Objeto {
public:
    QVector<Ponto3D> pontos;  //Agora armazenando Ponto3D corretamente
    QVector<QPair<int, int>> arestas;
};
#endif // STRUCTS_H
