#include <iostream>
#include <iomanip>

/*
ЗАМЕЧАНИЯ
1. Не используйте глобальные переменные. Создайте пространство имён и добавьте их туда. 
2. Зачем на каждом шаге проверять не последний ли элемент? Запустите цикл до предпоследнего, а потом распечатайте последний.
3. Для работы с размерами и индексами используйте тип size_t. 
4. Если вы генерируйте массивы и матрицы, то вам следовало бы их печатать — а то что мы проверяем?

    ИСПРАВЛЕНО (п.1):
    Глобальная константа перенесена в пространство имён
*/
namespace config
{
    const size_t MAX_ARRAY_SIZE = 100;
}

/*
    Поиск номера последнего минимального элемента
*/
size_t findLastMinIndex(const double arr[], size_t size)
{
    double minValue = arr[0];
    size_t lastMinIndex = 0;

    for (size_t i = 1; i < size; ++i)
    {
        if (arr[i] <= minValue)
        {
            minValue = arr[i];
            lastMinIndex = i;
        }
    }

    return lastMinIndex;
}

/*
    ИСПРАВЛЕНО (п.2):
    Вывод массива без проверки "последний / не последний"
*/
void printArray(const double arr[], size_t size)
{
    for (size_t i = 0; i + 1 < size; ++i)
        std::cout << std::fixed << std::setprecision(2) << arr[i] << ", ";

    std::cout << std::fixed << std::setprecision(2)
              << arr[size - 1] << std::endl;
}

int main()
{
    double array[config::MAX_ARRAY_SIZE];

    /*
        ИСПРАВЛЕНО (п.3):
        Для размеров и индексов используется size_t
    */
    size_t n;

    std::cout << "Enter array size (1-" << config::MAX_ARRAY_SIZE << "): ";
    std::cin >> n;

    if (n == 0 || n > config::MAX_ARRAY_SIZE)
    {
        std::cout << "Error: invalid array size" << std::endl;
        return 1;
    }

    std::cout << "Enter " << n << " real numbers:" << std::endl;
    for (size_t i = 0; i < n; ++i)
    {
        std::cout << "Element " << i << ": ";
        std::cin >> array[i];
    }

    /*
        ИСПРАВЛЕНО (п.4):
        Массив выводится на экран для проверки
    */
    std::cout << "\nArray elements:" << std::endl;
    printArray(array, n);

    size_t lastMinIndex = findLastMinIndex(array, n);

    std::cout << "\nLast minimum element index: "
              << lastMinIndex << std::endl;

    std::cout << "Value: "
              << std::fixed << std::setprecision(2)
              << array[lastMinIndex] << std::endl;

    return 0;
}
