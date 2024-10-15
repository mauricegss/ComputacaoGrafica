// DisplayObject.cpp
#include "DisplayObject.h"

DisplayObject::DisplayObject(const QString& name, ObjectType type, const QVector<QPoint>& points)
    : name(name), type(type), points(points) {}

QString DisplayObject::getName() const {
    return name;
}

ObjectType DisplayObject::getType() const {
    return type;
}

QVector<QPoint> DisplayObject::getPoints() const {
    return points;
}
