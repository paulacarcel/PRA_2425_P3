#ifndef DICT_H
#define DICT_H

#include <string>
#include <stdexcept>

template <typename V>
class Dict {
public:
    // Inserta key->value; lanza excepción si key ya existe
    virtual void insert(std::string key, V value) = 0;

    // Busca key; devuelve valor si existe, si no lanza excepción
    virtual V search(std::string key) = 0;

    // Elimina key->value; devuelve el valor eliminado; lanza excepción si no existe
    virtual V remove(std::string key) = 0;

    // Devuelve el número de entradas del diccionario
    virtual int entries() = 0;

    // Virtual destructor por seguridad en clases base
    virtual ~Dict() {}
};

#endif

