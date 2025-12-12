#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree {
private:
    int nelem;              // número de elementos
    BSNode<T>* root;        // nodo raíz

    // búsqueda recursiva
    BSNode<T>* search(BSNode<T>* n, T e) const {
        if (n == nullptr)
            throw std::runtime_error("Elemento no encontrado");
        else if (n->elem < e)
            return search(n->right, e);
        else if (n->elem > e)
            return search(n->left, e);
        else
            return n;
    }

    // inserción recursiva
    BSNode<T>* insert(BSNode<T>* n, T e) {
        if (n == nullptr) {
            nelem++;
            return new BSNode<T>(e);
        } else if (n->elem == e) {
            throw std::runtime_error("Elemento duplicado");
        } else if (n->elem < e) {
            n->right = insert(n->right, e);
        } else {
            n->left = insert(n->left, e);
        }
        return n;
    }

    // recorrido inorden
    void print_inorder(std::ostream &out, BSNode<T>* n) const {
        if (n != nullptr) {
            print_inorder(out, n->left);
            out << n->elem << " ";
            print_inorder(out, n->right);
        }
    }

    // eliminación recursiva
    BSNode<T>* remove(BSNode<T>* n, T e) {
        if (n == nullptr)
            throw std::runtime_error("Elemento no encontrado");
        else if (n->elem < e) {
            n->right = remove(n->right, e);
        } else if (n->elem > e) {
            n->left = remove(n->left, e);
        } else {
            // caso encontrado
            if (n->left != nullptr && n->right != nullptr) {
                n->elem = max(n->left);
                n->left = remove_max(n->left);
            } else {
                BSNode<T>* tmp = (n->left != nullptr) ? n->left : n->right;
                delete n;
                nelem--;
                return tmp;
            }
        }
        return n;
    }

    // máximo en subárbol
    T max(BSNode<T>* n) const {
        if (n == nullptr)
            throw std::runtime_error("Árbol vacío");
        else if (n->right != nullptr)
            return max(n->right);
        else
            return n->elem;
    }

    // eliminar máximo
    BSNode<T>* remove_max(BSNode<T>* n) {
        if (n->right == nullptr) {
            BSNode<T>* tmp = n->left;
            delete n;
            nelem--;
            return tmp;
        } else {
            n->right = remove_max(n->right);
            return n;
        }
    }

    // liberar memoria
    void delete_cascade(BSNode<T>* n) {
        if (n != nullptr) {
            delete_cascade(n->left);
            delete_cascade(n->right);
            delete n;
        }
    }

public:
    // constructor
    BSTree() : nelem(0), root(nullptr) {}

    // destructor
    ~BSTree() {
        delete_cascade(root);
    }

    // tamaño
    int size() const { return nelem; }

    // búsqueda lanzadera
    T search(T e) const {
        return search(root, e)->elem;
    }

    // operador []
    T operator[](T e) const {
        return search(e);
    }

    // inserción lanzadera
    void insert(T e) {
        root = insert(root, e);
    }

    // eliminación lanzadera
    void remove(T e) {
        root = remove(root, e);
    }

    // impresión inorden
    friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst) {
        bst.print_inorder(out, bst.root);
        return out;
    }
};

#endif
