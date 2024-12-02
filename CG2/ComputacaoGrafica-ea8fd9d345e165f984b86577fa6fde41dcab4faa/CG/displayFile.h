#ifndef DISPLAYFILE_H
#define DISPLAYFILE_H

#include <QVector>
#include "Matriz.h"

class DisplayFile {
public:
    DisplayFile() = default;

    void adicionarObjeto(const Matriz& objeto) {
        objetos.append(objeto);
    }

    QVector<Matriz>& getObjetos() {
        return objetos;
    }

    Matriz& getObjeto(int index) {
        return objetos[index];
    }

    int size() const {
        return objetos.size();
    }

    void setObjeto(int index, const Matriz& objeto) {
        if (index >= 0 && index < objetos.size()) {
            objetos[index] = objeto;
        }
    }

    Matriz& operator[](int index) {
        return objetos[index];
    }

    const Matriz& operator[](int index) const {
        return objetos[index];
    }

private:
    QVector<Matriz> objetos;
};

#endif // DISPLAYFILE_H
