# Vector Class


## _std::vector_ ir mano sukurto _Vector_ užpildymas _int_ elementais naudojant _push_back()_ funkciją

| **Duomenų kiekis** | **std::vector** | **Vector** |
|------------|-----------------|-------------|
| **100000** | **0.0019934** | **0.0019946** |
| **1000000** | **0.0179456** | **0.0199455** |
| **10000000** | **0.172693** | **0.207444** |
| **100000000** | **1.60069** | **1.730106** |
| **1000000000** | **15.6731** | **16.2667** |

## Atminties perskirtymai užpildant 100000000 elementų:
|**std::vector** ir **Vector**| **28 kartus įvyksta konteinerių atminties perskirstymai** |
|-|-|

## Versijos v1.5 palyginimas su _std::vector_ ir  _sukurtos Vector class_

### **Failo nuskaitymas:**

|**Duomenų kiekis**|**v1.5 su sukurta Vector class**|**v1.5 su std::vector**|
|------------------|-----------------------|--------------------------------|
|**1000**|**0.0399974**|**0.0079786**|
|**10000**|**0.0538023**|**0.0588678**|
|**100000**|**0.473766**|**0.542292**|
|**1000000**|**4.58024**|**5.39686**|
|**10000000**|**47.1932**|**55.3152**|

### **Saunuolių ir vargšiukų suskirstymas:**
|**Duomenų kiekis**|**v1.5 su sukurta Vector class**|**v1.5 su std::vector**|
|------------------|-----------------------|--------------------------------|
|**1000**|**0.0039897**|**0.0039886**|
|**10000**|**0.0518614**|**0.0468469**|
|**100000**|**0.74897**|**0.561533**|
|**1000000**|**10.4493**|**7.19394**|
|**10000000**|**97.389**|**88.6282**|

### **Saunuolių surašymas į failą:**
|**Duomenų kiekis**|**v1.5 su sukurta Vector class**|**v1.5 su std::vector**|
|------------------|-----------------------|--------------------------------|
|**1000**|**0.0079807**|**0.0069768**|
|**10000**|**0.0489826**|**0.0319145**|
|**100000**|**0.27382**|**0.26634**|
|**1000000**|**2.66284**|**2.62122**|
|**10000000**|**26.1167**|**25.7436**|

### **Vargšų surašymas į failą:**
|**Duomenų kiekis**|**v1.5 su sukurta Vector class**|**v1.5 su std::vector**|
|------------------|-----------------------|--------------------------------|
|**1000**|**0.0039892**|**0.0049827**|
|**10000**|**0.0438825**|**0.0319152**|
|**100000**|**0.270276**|**0.263057**|
|**1000000**|**2.60184**|**2.60185**|
|**10000000**|**26.2286**|**26.1187**|



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
