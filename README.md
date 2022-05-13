# Vector Class


## _std::vector_ ir mano sukurto _Vector_ užpildymas _int_ elementais naudojant _push_back()_ funkciją

| **Kiekis** | **std::vector** | **Vector** |
|------------|-----------------|-------------|
| **100000** | **0.0019953** | **0.0019952** |
| **1000000** | **0.0189438** | **0.0109698** |
| **10000000** | **0.1605** | **0.105948** |
| **100000000** | **1.54952** | **0.961934** |
| **1000000000** | **15.2216** | **9.30689** |

## Atminties perskirtymai užpildant 100000000 elementų:
|**std::vector** ir **Vector**| **28 kartus įvyksta konteinerių atminties perskirstymai** |
|-|-|

## Funkcijų aprašymai: 
### 1. Prideda elementą prie vektoriaus pabaigos
```
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
```
### 2. Iš vektoriaus pabaigos pašalina elementą
```
template<typename Type>
void Vector<Type>::popBack()
{
    if (count_ == 0) {
        throw "Err";
    }

    data_[count_ - 1].~Type();
    --count_;
}
```
### 3. Išvalo
```
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
```
### 4. Pakeičia vektoriaus dydį
```
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
```
### 5. Pasiekia paskutini vektoriaus elementą
```
template<typename Type>
const Type& Vector<Type>::back() const
{
    if(count_ > 0) {
        return data_[count_ - 1];
    }
    throw "Err";
}
```
