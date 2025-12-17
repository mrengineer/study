#include <iostream>

/*
    ИСПРАВЛЕНО (п.1):
    Глобальная константа перенесена в пространство имён
*/
namespace config
{
    const size_t MAX_SIZE = 10;
}

/*
    Вывод квадратной матрицы n x n
*/
void printMatrix(const int matrix[][config::MAX_SIZE], size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = 0; j < size; ++j)
            std::cout << matrix[i][j] << "\t";
        std::cout << std::endl;
    }
}

/*
    Поиск последнего чётного элемента в строке
*/
int findLastEvenInRow(const int row[], size_t size)
{
    int lastEven = -1;

    for (size_t j = 0; j < size; ++j)
        if (row[j] % 2 == 0)
            lastEven = row[j];

    return lastEven;
}

/*
    Формирование массива из последних чётных элементов строк
*/
void fillEvenNumbersArray(const int matrix[][config::MAX_SIZE],
                          size_t size,
                          int result[])
{
    for (size_t i = 0; i < size; ++i)
        result[i] = findLastEvenInRow(matrix[i], size);
}

int main()
{
    int matrix[config::MAX_SIZE][config::MAX_SIZE];
    int evenNumbers[config::MAX_SIZE];

    /*
        ИСПРАВЛЕНО (п.3):
        Для размеров и индексов используется size_t
    */
    size_t matrixSize;

    std::cout << "Enter matrix size (n x n, n <= " << config::MAX_SIZE << "): ";
    std::cin >> matrixSize;

    if (matrixSize == 0 || matrixSize > config::MAX_SIZE)
    {
        std::cout << "Invalid size" << std::endl;
        return 1;
    }

    std::cout << "Enter matrix elements:" << std::endl;
    for (size_t i = 0; i < matrixSize; ++i)
        for (size_t j = 0; j < matrixSize; ++j)
        {
            std::cout << "Element [" << i << "][" << j << "]: ";
            std::cin >> matrix[i][j];
        }

    /*
        ИСПРАВЛЕНО (п.4):
        Матрица выводится для проверки
    */
    std::cout << "\nOriginal matrix:" << std::endl;
    printMatrix(matrix, matrixSize);

    fillEvenNumbersArray(matrix, matrixSize, evenNumbers);

    /*
        ИСПРАВЛЕНО (п.2):
        Нет проверки "последний / не последний" при выводе
    */
    std::cout << "\nLast even numbers in each row:" << std::endl;
    for (size_t i = 0; i < matrixSize; ++i)
    {
        std::cout << "Row " << i << ": ";
        if (evenNumbers[i] != -1)
            std::cout << evenNumbers[i];
        else
            std::cout << "No even number";
        std::cout << std::endl;
    }

    return 0;
}
