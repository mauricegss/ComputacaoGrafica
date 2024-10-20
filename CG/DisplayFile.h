// DisplayFile.h
#ifndef DISPLAYFILE_H
#define DISPLAYFILE_H

#include "displayobject.h"
#include <QVector>

class DisplayFile {
public:
    void addObject(const DisplayObject& obj);
    QVector<DisplayObject> getObjects() const;

private:
    QVector<DisplayObject> objects;
};

#endif // DISPLAYFILE_H
