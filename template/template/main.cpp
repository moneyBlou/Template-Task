#include <iostream>
#include <vector>
#include <string>

using namespace std;


struct Person {
    string lastName;
    int age;


    Person(string lastName, int age) : lastName(lastName), age(age) {}

    // Перегрузка оператора вывода << для удобного вывода объектов Person
    // Это позволяет выводить объекты Person в cout с использованием оператора <<
    friend ostream& operator<<(ostream& os, const Person& person) {
        os << person.lastName << " (" << person.age << ")"; // Форматированный вывод
        return os;
    }
};

// Шаблонная функция swap: меняет местами значения двух переменных одного типа.
// template <typename T>:  делает функцию универсальной, работающей с разными типами данных.
template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// Шаблонная функция для разделения массива (вектора)
template <typename T, typename Compare>
int partition(vector<T>& arr, int low, int high, Compare comp) {
    T pivot = arr[high]; // Опорным элементом является последний элемент
    int i = (low - 1);   // Индекс элемента, который меньше опорного

    // Проходим по подмассиву от low до high-1
    for (int j = low; j <= high - 1; j++) {
        // Если текущий элемент меньше опорного (используем функтор comp)
        if (comp(arr[j], pivot)) {
            i++;                // Увеличиваем индекс i
            ::swap(arr[i], arr[j]); // Меняем местами arr[i] и arr[j], вызываем нашу swap
        }
    }
    ::swap(arr[i + 1], arr[high]); // Меняем местами опорный элемент и arr[i+1], вызываем нашу swap
    return (i + 1);             // Возвращаем индекс опорного элемента
}

// Шаблонная функция quickSort: реализует алгоритм быстрой сортировки.
template <typename T, typename Compare>
void quickSort(vector<T>& arr, int low, int high, Compare comp) {
    // Базовый случай рекурсии: если подмассив содержит 0 или 1 элемент, то он уже отсортирован.
    if (low < high) {
        // Разделяем массив на две части относительно опорного элемента
        int pi = partition(arr, low, high, comp); // Получаем индекс опорного элемента

        // Рекурсивно сортируем левую часть массива (элементы меньше опорного)
        quickSort(arr, low, pi - 1, comp);

        // Рекурсивно сортируем правую часть массива (элементы больше опорного)
        quickSort(arr, pi + 1, high, comp);
    }
}

// Шаблонная функция для вывода массива
template <typename T>
void printArray(const vector<T>& arr) {
    for (const T& x : arr) {
        cout << x << " ";
    }
    cout << endl;
}


int main() {
    // Пример с целыми числами
    vector<int> intArr = { 10, 7, 8, 9, 1, 5 }; // Создаем вектор целых чисел
    int nInt = intArr.size();                 // Получаем размер вектора

    cout << "Исходный массив целых чисел: "; // Выводим сообщение
    printArray(intArr);                       // Выводим элементы массива

    quickSort(intArr, 0, nInt - 1, [](int a, int b) { return a <= b; });

    cout << "Отсортированный массив целых чисел: ";
    printArray(intArr);

    // Пример с типом Person (сортировка по фамилии)
    vector<Person> people = {
        {"Иванов", 30},      // Создаем объект Person
        {"Петров", 25},      // Создаем объект Person
        {"Сидоров", 40},     // Создаем объект Person
        {"Смирнов", 20}      // Создаем объект Person
    };
    int nPeople = people.size();                 // Получаем размер вектора людей

    cout << "\nИсходный массив людей: ";   // Выводим сообщение
    printArray(people);                            // Выводим исходный массив людей

    // Сортировка людей по фамилии (используем лямбда-выражение для сравнения)
    // [](const Person& a, const Person& b) { return a.lastName <= b.lastName; } -
    //   Лямбда-выражение, принимающее два объекта Person a и b и возвращающее true, если фамилия a меньше или равна фамилии b.
    quickSort(people, 0, nPeople - 1, [](const Person& a, const Person& b) {
        return a.lastName <= b.lastName;
        });

    cout << "Отсортированный массив людей (по фамилии): "; // Выводим сообщение
    printArray(people);                                          // Выводим отсортированный массив людей

    // Пример с типом Person (сортировка по возрасту)
    cout << "\nИсходный массив людей: ";
    printArray(people);

    // Сортировка людей по возрасту (используем лямбда-выражение для сравнения)
    //   Лямбда-выражение, принимающее два объекта Person a и b и возвращающее true, если возраст a меньше или равен возрасту b.
    quickSort(people, 0, nPeople - 1, [](const Person& a, const Person& b) {
        return a.age <= b.age;
        });

    cout << "Отсортированный массив людей (по возрасту): ";
    printArray(people);

    return 0;
}
