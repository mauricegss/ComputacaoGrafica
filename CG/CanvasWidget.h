// CanvasWidget.h
#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include "DisplayFile.h"

class CanvasWidget : public QWidget {
    Q_OBJECT

public:
    explicit CanvasWidget(QWidget *parent = nullptr);

    void setDisplayFile(DisplayFile* displayFile);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    DisplayFile* displayFile;
};

#endif // CANVASWIDGET_H
