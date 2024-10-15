// DisplayFile.cpp
#include "DisplayFile.h"

void DisplayFile::addObject(const DisplayObject& obj) {
    objects.append(obj);
}

QVector<DisplayObject> DisplayFile::getObjects() const {
    return objects;
}
