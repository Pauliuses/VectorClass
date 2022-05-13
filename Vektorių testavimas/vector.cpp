#include "vector.h"

template<typename Type>
Vector<Type>::Vector()
    : data_{nullptr}, count_{0}, capacity_{0}
{
}

template<typename Type>
Vector<Type>::Vector(const Vector<Type>& other)
    : data_{nullptr}, count_{other.count_}, capacity_{other.capacity_}
{
    if (capacity_ != 0) {
        data_ = new Type[capacity_];
        std::copy(other.data_, other.data_ + count_, data_);
    }
}

template<typename Type>
Vector<Type>::Vector(Vector<Type>&& other)
    : Vector()
{
    swap(other);
}

template<typename Type>
Vector<Type>& Vector<Type>::operator=(const Vector<Type>& other)
{
    if (this != &other) {
        Vector<Type> tmp(other);
        tmp.swap(*this);
    }
    return *this;
}

template<typename Type>
Vector<Type>& Vector<Type>::operator=(Vector<Type>&& other)
{
    swap(other);
    return *this;
}

template<typename Type>
Vector<Type>::~Vector()
{
    clear();
}

template<typename Type>
void Vector<Type>::reserve(std::size_t size)
{
    if (size <= capacity_) {
        return;
    }

    std::size_t newCapacity = capacity_ * 2;
    if (newCapacity == 0) {
        newCapacity = 1;
    }
    while (size > newCapacity) {
        newCapacity *= 2;
        if (newCapacity < capacity_) {
            newCapacity = maxSize();
            break;
        }
    }
    Type* newData = new Type[newCapacity];
    std::copy(data_, data_ + count_, newData);

    delete[] data_;
    data_ = newData;
    capacity_ = newCapacity;
}

template<typename Type>
void Vector<Type>::pushBack(const Type& element)
{
    if (count_ == capacity_) {
        if (capacity_ == maxSize()) {
            throw "LengthError";
        }
        reserve(capacity_ + 1);
    }

    data_[count_] = element;
    ++count_;
}

template<typename Type>
void Vector<Type>::popBack()
{
    if (count_ == 0) {
        throw "Err";
    }

    data_[count_ - 1].~Type();
    --count_;
}

template<typename Type>
void Vector<Type>::assign(std::size_t count, const Type& value)
{
    reserve(count);
    for (std::size_t i = 0; i < count; i++) {
        data_[i] = value;
    }
    if (count > count_) {
        count_ = count;
    }
}

template<typename Type>
const Type& Vector<Type>::back() const
{
    if(count_ > 0) {
        return data_[count_ - 1];
    }
    throw "Err";
}

template<typename Type>
const Type& Vector<Type>::front() const
{
    if(count_ > 0) {
        return data_[0];
    }
    throw "Err";
}

template<typename Type>
std::size_t Vector<Type>::capacity() const
{
    return capacity_;
}

template<typename Type>
std::size_t Vector<Type>::size() const
{
    return count_;
}

template <typename Type>
std::size_t Vector<Type>::maxSize() const
{
    return std::numeric_limits<std::size_t>::max();
}

template<typename Type>
bool Vector<Type>::empty() const
{
    return count_ == 0;
}

template<typename Type>
void Vector<Type>::clear()
{
    if (data_ != nullptr) {
        delete[] data_;
        data_ = nullptr;
        count_ = 0;
        capacity_ = 0;
    }
}

template<typename Type>
void Vector<Type>::resize(std::size_t count)
{
    if (count <= count_) {
        while (count_ > count) {
            popBack();
            -- count_;
        }
        return;
    }

    reserve(count);

    while(count_ < count) {
        data_[count_] = Type();
        ++count_;
    }
}

template<typename Type>
void Vector<Type>::shrinkToFit()
{
    if (count_ == 0) {
        clear();
        return;
    }

    if (count_ <= (capacity_ / 2)) {
        std::size_t newCapacity = capacity_ / 2;
        while (count_ <= (newCapacity / 2)) {
            newCapacity /= 2;
        }
        Type* newData = new Type[newCapacity];
        std::copy(data_, data_ + count_, newData);

        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
    }
}

template<typename Type>
Type& Vector<Type>::at(std::size_t index)
{
    if (index < count_) {
        return data_[index];
    }
    throw "IndexOutOfRange";
}

template<typename Type>
const Type& Vector<Type>::at(std::size_t index) const
{
    if (index < count_) {
        return data_[index];
    }
    throw "IndexOutOfRange";
}

template<typename Type>
Type& Vector<Type>::operator[](std::size_t index)
{
    return data_[index];
}

template<typename Type>
const Type& Vector<Type>::operator[](std::size_t index) const
{
    return data_[index];
}

template <class Type>
template <class ...Args>
void Vector<Type>::emplaceBack(Args&&... args)
{
    pushBack(std::move(Type(args...)));
}

template<class Type>
void Vector<Type>::swap(Vector<Type>& other)
{
    std::swap(data_, other.data_);
    std::swap(count_, other.count_);
    std::swap(capacity_, other.capacity_);
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const Vector<T> &v)
{
    if (v.empty()) {
        out << "";
    }

    for (std::size_t i = 0; i < v.size(); i++) {
        out << v[i] << " ";
    }

    return out;
}
