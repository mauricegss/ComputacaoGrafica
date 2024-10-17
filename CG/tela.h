// Tela.h
#ifndef TELA_H
#define TELA_H

#include <QWidget>
#include "displayfile.h"

class Tela : public QWidget {
    Q_OBJECT

public:
    explicit Tela(QWidget *parent = nullptr) : QWidget(parent), displayFile(nullptr) {}

    void setDisplayFile(DisplayFile* displayFile);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    DisplayFile* displayFile;
};

#endif // TELA_H
