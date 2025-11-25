#ifndef NODE_H
#define NODE_H

#include <ostream>  // necesario para std::ostream

// Clase genérica Node<T>
template <typename T>
class Node {
public:
    T data;          // elemento almacenado
    Node<T>* next;   // puntero al siguiente nodo

    // Constructor: inicializa los atributos
    Node(T data, Node<T>* next = nullptr) {
        this->data = data;
        this->next = next;
    }

    // Sobrecarga del operador << para imprimir el nodo
    friend std::ostream& operator<<(std::ostream &out, const Node<T> &node) {
        out << node.data;
        return out;
    }
};

#endif

