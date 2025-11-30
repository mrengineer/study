#include <iostream>

bool hasAllUniqueDigits(int number);
void removeElementsWithUniqueDigits(int*& array, size_t& size);
void printArray(const int array[], size_t size);


// Код изменен в соотвествии с замечанями:
// bool hasAllUniqueDigits(int n) — исправлена логика однозначных чисел
// void removeElementsWithUniqueDigits(int*& arr, size_t& size)
// Эта функция заменяет массив "на месте" чтобы эффективнее 
// применять динамические массивы

int main()
{
    size_t arraySize;
    std::cout << "Enter array size: ";
    std::cin >> arraySize;

    int* array = new int[arraySize];

    std::cout << "Enter array elements:" << std::endl;
    for (size_t i = 0; i < arraySize; ++i)
    {
        std::cout << "Element [" << i << "]: ";
        std::cin >> array[i];
    }

    std::cout << "\nOriginal array:" << std::endl;
    printArray(array, arraySize);

    removeElementsWithUniqueDigits(array, arraySize);

    std::cout << "\nArray after removing elements with all unique digits:" << std::endl;

    if (arraySize > 0)
        printArray(array, arraySize);
    else
        std::cout << "Array is empty\n";

    delete[] array;

    return 0;
}

bool hasAllUniqueDigits(int number)
{
    if (number < 0)
        number = -number;

    // Однозначное число — его единственная цифра уникальна
    if (number < 10)
        return true;

    bool used[10] = {false};

    while (number > 0)
    {
        int d = number % 10;
        if (used[d])
            return false;

        used[d] = true;
        number /= 10;
    }

    return true;
}

void removeElementsWithUniqueDigits(int*& array, size_t& size)
{
    // Считаем количество элементов, которые нужно оставить
    size_t keepCount = 0;
    for (size_t i = 0; i < size; ++i)
    {
        if (!hasAllUniqueDigits(array[i]))
            ++keepCount;
    }

    // Нет элементов → освобождаем и обнуляем
    if (keepCount == 0)
    {
        delete[] array;
        array = nullptr;
        size = 0;
        return;
    }

    int* newArray = new int[keepCount];
    size_t idx = 0;

    for (size_t i = 0; i < size; ++i)
    {
        if (!hasAllUniqueDigits(array[i]))
        {
            newArray[idx++] = array[i];
        }
    }

    delete[] array;      // освобождаем старую память
    array = newArray;    // подменяем указатель
    size = keepCount;    // обновляем размер
}

void printArray(const int array[], size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        std::cout << array[i];
        if (i < size - 1)
            std::cout << " ";
    }
    std::cout << "\n";
}
