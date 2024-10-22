// DisplayObject.cpp
#include "displayobject.h"

DisplayObject::DisplayObject(const QString& nome, ObjectType tipo, const QVector<QPoint>& pontos)
    : nome(nome), tipo(tipo), pontos(pontos) {}

QString DisplayObject::getNome() const {
    return nome;
}

ObjectType DisplayObject::getTipo() const {
    return tipo;
}

QVector<QPoint> DisplayObject::getPontos() const {
    return pontos;
}
