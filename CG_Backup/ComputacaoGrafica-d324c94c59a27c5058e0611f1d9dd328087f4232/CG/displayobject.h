// DisplayObject.h
#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H

#include <QVector>
#include <QString>
#include <QPoint>

enum ObjectType { PointType, LineType, PolygonType };

class DisplayObject {
public:
    DisplayObject(const QString& nome, ObjectType tipo, const QVector<QPoint>& pontos);

    QString getNome() const;
    ObjectType getTipo() const;
    QVector<QPoint> getPontos() const;

private:
    QString nome;
    ObjectType tipo;
    QVector<QPoint> pontos;  // Lista de pontos
};

#endif // DISPLAYOBJECT_H
