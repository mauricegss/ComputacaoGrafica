// DisplayFile.cpp
#include "displayfile.h"

void DisplayFile::addObject(const DisplayObject& obj) {
    objects.append(obj);
}

QVector<DisplayObject> DisplayFile::getObjects() const {
    return objects;
}
