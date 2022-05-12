# Vector Class


## _std::vector_ ir mano sukurto _Vectors_ užpildymas _int_ elementais naudojant _push_back()_ funkciją

| **Kiekis** | **std::vector** | **Vectors** |
|------------|-----------------|-------------|
| **10000** | **0.0009697** | **0.0009973**|
| **100000** | **0.0019844** | 0.0020218 |
| **1000000** | **0.0179338** | **0.0209437** |
| **10000000** | **0.16554** | **0.201517** |
| **100000000** | **1.66784** | **1.83895** |
| **1000000000** | **15.8316** | **17.0923** |

## Atminties perskirtymai užpildant 100000000 elementų:
|**std::vector** ir **Vectors**| **27 kartus įvyksta konteinerių atminties perskirstymai** |
|-|-|

## Funkcijų aprašymai: 
### Sunaikina ir atlaisvina vieta
```
template <class T> void Vectors<T>::destroy(){
        if(data){
            iterator it = avail;
            while(it != data)
                alloc.destroy(--it);
                alloc.deallocate(data, limit - data);
        }
        data = limit = avail = nullptr;
}
```
### Išskiria vietos j-i elementams ir nukopijuoja elementus iš intervalo
```
template <class T> void Vectors<T>::create(const_iterator i, const_iterator j){
        data = alloc.allocate(j - i);
        limit = avail = uninitialized_copy(i, j, data);
        actualsize = (j - 1);
}
```
Padvigubina vietos, išskiria vietą ir perkopijuoja egzistuojančius elementus bei resetina rodykles į naujai išskirtą vietą
```
template <class T> void Vectors<T>::grow(){
        size_type new_size = std::max(2 * (limit - data), ptrdiff_t(1));
        iterator new_data = alloc.allocate(new_size);
        iterator new_avail = std::uninitialized_copy(data, avail, new_data);
        destroy();
        data = new_data;
        avail = new_avail;
        limit = data + new_size;
}
```
Pointina į išskirtą bet neinicializuotą vietą
```
template <class T> void Vectors<T>::append(const T& val){
        alloc.construct(avail++, val);
}
```
Patikrina ar yra už ribų
```
template <class T> T Vectors<T>::at(size_type i){
	if(!(data[i])){
		throw new std::domain_error("Uz ribu!");
		return nullptr;
	} else {
		return data[i];
	}
}
```
