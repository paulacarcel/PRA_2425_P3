#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include <vector>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict: public Dict<V> {
private:
    BSTree<TableEntry<V>>* tree;   // ABB de entradas clave->valor

public:
    // Constructor: crea un ABB vacío
    BSTreeDict() {
        tree = new BSTree<TableEntry<V>>();
    }

    // Destructor: libera memoria
    ~BSTreeDict() {
        delete tree;
    }

    // Inserción: delega en BSTree
    void insert(std::string key, V value) override {
        TableEntry<V> entry(key, value);
        tree->insert(entry);
    }

    // Búsqueda: delega en BSTree
    V search(std::string key) const override {
        TableEntry<V> dummy(key, V()); // entrada ficticia con clave
        TableEntry<V> result = tree->search(dummy);
        return result.getValue();
    }

    // Eliminación: delega en BSTree
    void remove(std::string key) override {
        TableEntry<V> dummy(key, V());
        tree->remove(dummy);
    }

    // Devuelve todas las entradas como vector
    std::vector<TableEntry<V>> entries() const override {
        // Para simplificar, podemos recorrer el árbol usando << en un stringstream
        // o implementar un método adicional en BSTree que devuelva un vector.
        // Aquí asumimos que BSTree tiene un método auxiliar inorder_entries().
        std::vector<TableEntry<V>> result;
        tree->inorder_entries(result);
        return result;
    }

    // Sobrecarga del operador []
    V operator[](std::string key) {
        return search(key);
    }

    // Sobrecarga del operador << para imprimir el diccionario
    friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs) {
        out << *(bs.tree);
        return out;
    }
};

#endif
