# Vector Class


## _std::vector_ ir mano sukurto _Vector_ užpildymas _int_ elementais naudojant _push_back()_ funkciją

| **Kiekis** | **std::vector** | **Vector** |
|------------|-----------------|-------------|
| **100000** | **0.0019934** | **0.0019946** |
| **1000000** | **0.0179456** | **0.0199455** |
| **10000000** | **0.172693** | **0.207444** |
| **100000000** | **1.60069** | **1.730106** |
| **1000000000** | **15.6731** | **16.2667** |

## Atminties perskirtymai užpildant 100000000 elementų:
|**std::vector** ir **Vector**| **28 kartus įvyksta konteinerių atminties perskirstymai** |
|-|-|

## Funkcijų aprašymai: 
### 1. Prideda elementą prie vektoriaus pabaigos
```
template <typename T>
void Vector<T>::push_back(const T &val)
{
    if (avail == limit)
        Grow();
    Unchecked_append(val);
}
```
### 2. Iš vektoriaus pabaigos pašalina elementą
```
template <typename T>
void Vector<T>::pop_back()
{
    alloc.destroy(--avail);
}
```
### 3. Ištrina elementą
```
template <typename T>
void Vector<T>::erase(Vector<T>::const_iterator position)
{
    if (position < data || position > avail)
        throw std::out_of_range{"Out of bounds."};
    iterator new_avail = std::move(position + 1, avail, position);
    alloc.destroy(new_avail);
    avail = new_avail;
}
```
### 4. Pakeičia vektoriaus dydį
```
template <typename T>
void Vector<T>::resize(size_t n, const T &value)
{
    if (n > capacity())
    {
        Grow();
        resize(n, value);
    }
    else if (n > size())
    {
        avail += (n - size());

        for (size_t i = size(); i < n; i++)
        {
            data[i] = value;
        }
    }
    else
        resize(n);
}
```
### 5. Sumažina dydį
```
template <typename T>
void Vector<T>::shrink_to_fit()
{
    if (avail < limit)
        limit = avail;
}
```
