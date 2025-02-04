#ifndef LEITOROBJ_H
#define LEITOROBJ_H
#include <QString>
#include <QVector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "structs.h"
#include "matriz.h"
#include <QPointF>

class OBJFileReader {
public:
    OBJFileReader() = default;

    bool readOBJ(const QString &filename, QVector<Ponto3D> &vertices, QVector<Face> &faces);

    // Novo método para criar um objeto Matriz a partir de um arquivo OBJ
    Matriz lerMatriz(const QString &filename, const QString &nomeObjeto);

    // Estrutura retornada pelo método LerArquivo
    struct Objeto {
        QVector<Ponto3D> pontos;  // Lista de pontos normalizados
        QVector<QPair<int, int>> arestas; // Lista de arestas (índices dos pontos)
    };

    // Método que lê um arquivo OBJ e retorna um Objeto
    static Objeto LerArquivo(const QString& caminho);
};

#endif // LEITOROBJ_H
