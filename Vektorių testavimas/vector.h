#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <iostream>
#include <limits>

template<typename Type>
class Vector
{
  public:

    // konstruktorius
    Vector();

    // copy constructor
    Vector(const Vector& other);

    Vector& operator=(const Vector& other);

    Vector(Vector&& other);

    // priskyrimo
    Vector& operator=(Vector&& other);

    // destructor
    ~Vector();

    // Prideda elementą prie vektoriaus pabaigos
    void pushBack(const Type& element);

    // Iš vektoriaus pabaigos pašalina elementą
    void popBack();

    // Priskiria vertę
    void assign(std::size_t count, const Type& value);

    // Adresas į paskutinį vektoriaus elementą
    const Type& back() const;

    // Adresas į pirmąjį vektoriaus elementą
    const Type& front() const;

    // Esama vektoriaus talpa
    std::size_t capacity() const;

    // Vektoriaus dydis
    std::size_t size() const;

    // Didžiausias dydis
    std::size_t maxSize() const;

    // tuščias - tiesa
    bool empty() const;

    // Išvalo
    void clear();

    // Paskiria atminį
    void reserve(std::size_t size);

    // resize
    void resize(std::size_t count);

    // Sumažina dydį
    void shrinkToFit();

    Type& at(std::size_t index);

    const Type& at(std::size_t index) const;

    // Gražina adresą į elementą
    Type& operator[](std::size_t index);

    // Gražina pastovų elemento pozicijos adresą
    const Type& operator[](std::size_t index) const;

    template <class ...Args>
    void emplaceBack(Args&&... args);

  private:

    // Sukeičia reikšmes
    void swap(Vector& other);

    // Rodyklė į masyvą su duomenimis
    Type* data_;

    // Užpildymas
    std::size_t count_;

    // Dydis
    std::size_t capacity_;
};
#endif