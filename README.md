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


List(); *constructor*


List(std::shared_ptr<Element<T>>, List const&); *list-constructor used to pop front*


List(T, List const&); *list-constructor used to add head element*


List(List const&, T); *list-constructor used to add tail element*


bool IsEmpty() const; *is empty flag*


int Count() const; *get num of elements in List*


List<T> AddHead(T) const; *return new List with added head element*


List<T> AddTail(T) const; *return new List with added tail element*


List<T> Take(int) const; *take and return new List from 0 to int elements*


T Get(int) const; *get element of List by index*


List<T> Set(int, T) const; *set element of List by index*


List<T> Insert(T, int index = 0) const; *insert element in List by index*


List Remove(int) const; *delete element in List by index*


void PrintAll() const; *print all List*

### Array (динамический персистентный массив)


Array(); *constructor*


Array(std::shared_ptr<Element>, Array const&); *constructor used to add elements*


Array(int, Array const&); *constructor used to remove elements*


bool IsEmpty() const; *is empty flag*


int Count() const; *get num of elements in Array*


Array Add(const T&) const; *return new Array with added element*
		

Array Remove(const T&) const; *return new Array with removed element*


bool Find(const T&) const; *find element in Array*
		

void PrintAll() const; *print all elements from Array*

### HashTable (ассоциативный массив на основе хеш-таблицы)


HashTable(); *constructor*


HashTable(std::shared_ptr<Element>, HashTable const&); *constructor used to add elements*


HashTable(int, HashTable const&); *constructor used to remove elements*


bool IsEmpty() const; *is empty flag*


int Count() const; *get num of elements in HashTable*


void Hash(std::shared_ptr<Element> element, const HashFunction1& hash1 = HashFunction1(), const HashFunction2& hash2 = HashFunction2()); *change keys*


HashTable Add(const T&) const; *return new HashTable with added element*
		

HashTable Remove(const T&) const; *return new HashTable with removed element*


bool Find(const T&) const; *find element in HashTable*
		

void PrintAll() const; *print all elements from HashTable*
