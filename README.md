# Персистентные структуры данных

Задача:

Реализовать библиотеку со следующими структурами данных в персистентных вариантах:

* Динамический массив (константное время доступа, переменная длина)
* Двусвязный список
* Ассоциативный массив (на основе хеш-таблицы)

В базовом варианте решения персистентность может быть реализована на основе Fat Node.

Язык реализации: C++

Требования:

* Единый API для всех структур данных.

Дополнительные требования:

* Обеспечить произвольную вложенность данных (template).

* Реализовать более эффективное по скорости доступа данных решение по сравнению с Fat Node.

Предполагаемый путь решения

Персистентные структуры данных (persistent data structure, PDS) — это структуры данных, которые при внесении в них каких-то изменений сохраняют все свои предыдущие состояния и доступ к этим состояниям.

PDS можно реализовать, используя метод «толстых» узлов (Fat Node), при котором для каждого элемента структуры данных хранится история его состояний. Планируется сделать базовую реализацию этим методом, затем исследовать возможности более эффективной реализации.

Более эффективная реализация предполагает использование умных указателей (smart pointers, C++11) - [std::shared_ptr](https://en.cppreference.com/w/cpp/memory/shared_ptr).

Задача  | Сроки | Исполнитель
------------- | ------------- | -------------
Исследовали тему, нашли информацию о PDS | 24.11.22 | Данил, Мария
Рассмотрели возможности более эффективной реализации PDS | 24.11.22 | Данил
Реализовали базовую версию односвязного списка | 7.12.22 | Данил
Реализовали двусвязный список на основе smart pointers | 7.12.22 | Данил
Реализовали базовую версию динамического массива на основе fat node | 8.12.22 | Мария
Реализовали ассоциативный массив на основе хеш-таблицы с использованием smart pointers | 13.12.22 | Данил
Реализовали динамический массив использованием smart pointers | 14.12.22 | Мария
Составили документацию к проекту | 14.12.22 | Мария

## pdsLib
### List (двусвязный персистентный список)

/*constructor*/
List();

/*list-constructor used to pop front*/
List(std::shared_ptr<Element<T>>, List const&);

/*list-constructor used to add head element*/
List(T, List const&);

/*list-constructor used to add tail element*/
List(List const&, T);

/*is empty flag*/
bool IsEmpty() const;

/*get num of elements in List*/
int Count() const;

/*return new List with added head element*/
List<T> AddHead(T) const;

/*return new List with added tail element*/
List<T> AddTail(T) const;

/*take and return new List from 0 to int elements*/
List<T> Take(int) const;

/*get element of List by index*/
T Get(int) const;

/*set element of List by index*/
List<T> Set(int, T) const;

/*insert element in List by index*/
List<T> Insert(T, int index = 0) const;

/*delete element in List by index*/
List Remove(int) const;

/*print all List*/
void PrintAll() const;

### Array (динамический персистентный массив)

/*constructor*/
Array();

/*constructor used to add elements*/;
Array(std::shared_ptr<Element>, Array const&);

/*constructor used to remove elements*/
Array(int, Array const&);

/*is empty flag*/
bool IsEmpty() const;

/*get num of elements in Array*/
int Count() const;

/*return new Array with added element*/
Array Add(const T&) const;
		
/*return new Array with removed element*/
Array Remove(const T&) const;

/*find element in Array*/
bool Find(const T&) const;
		
/*print all elements from Array*/
void PrintAll() const;

### HashTable (ассоциативный массив на основе хеш-таблицы)

/*double hash method:
two hash functions that return coprime natural numbers*/
struct HashFunction1;
struct HashFunction2;

/*constructor*/
HashTable();

/*constructor used to add elements*/;
HashTable(std::shared_ptr<Element>, HashTable const&);

/*constructor used to remove elements*/
HashTable(int, HashTable const&);

/*is empty flag*/
bool IsEmpty() const;

/*get num of elements in HashTable*/
int Count() const;

/*change keys*/
void Hash(std::shared_ptr<Element> element, const HashFunction1& hash1 = HashFunction1(), const HashFunction2& hash2 = HashFunction2());

/*return new HashTable with added element*/
HashTable Add(const T&) const;
		
/*return new HashTable with removed element*/
HashTable Remove(const T&) const;

/*find element in HashTable*/
bool Find(const T&) const;
		
/*print all elements from HashTable*/
void PrintAll() const;
