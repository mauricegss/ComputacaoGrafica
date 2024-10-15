// DisplayObject.h
#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H

#include <QVector>
#include <QString>
#include <QPoint>

enum ObjectType { PointType, LineType, PolygonType };

class DisplayObject {
public:
    DisplayObject(const QString& name, ObjectType type, const QVector<QPoint>& points);

    QString getName() const;
    ObjectType getType() const;
    QVector<QPoint> getPoints() const;

private:
    QString name;
    ObjectType type;
    QVector<QPoint> points;  // Lista de pontos
};

#endif // DISPLAYOBJECT_H
