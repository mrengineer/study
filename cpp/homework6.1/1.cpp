#include <iostream>
#include <cstdlib>
#include <ctime>

/*
ЗАМЕЧАНИЯ
1. Не используйте глобальные переменные. Создайте пространство имён и добавьте их туда. 
2. Зачем на каждом шаге проверять не последний ли элемент? Запустите цикл до предпоследнего, а потом распечатайте последний.
3. Для работы с размерами и индексами используйте тип size_t. 
4. Если вы генерируйте массивы и матрицы, то вам следовало бы их печатать — а то что мы проверяем?

    ИСПРАВЛЕНО (п.1):
    Все ранее глобальные константы перенесены в пространство имён
*/
namespace config
{
    const size_t MAX_ARRAY_SIZE  = 100;
    const size_t MAX_MATRIX_ROWS = 10;
    const size_t MAX_MATRIX_COLS = 10;
    const int RAND_MIN_VAL = 0;
    const int RAND_MAX_VAL = 1024;
}

/*
    Подсчет элементов одномерного массива,
    не попадающих в диапазон [left; right]
*/
size_t countOutOfRangeArray(const int values[],
                            size_t length,
                            int left,
                            int right)
{
    size_t count = 0;

    for (size_t i = 0; i < length; ++i)
    {
        if (values[i] < left || values[i] > right)
            ++count;
    }
    return count;
}

/*
    Подсчет элементов двумерного массива,
    не попадающих в диапазон [left; right]
*/
size_t countOutOfRangeMatrix(const int values[][config::MAX_MATRIX_COLS],
                             size_t rows,
                             size_t cols,
                             int left,
                             int right)
{
    size_t count = 0;

    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            if (values[i][j] < left || values[i][j] > right)
                ++count;

    return count;
}

/*
    Заполнение одномерного массива случайными числами
*/
void fillRandomArray(int arr[], size_t length)
{
    for (size_t i = 0; i < length; ++i)
        arr[i] = config::RAND_MIN_VAL +
                 std::rand() % (config::RAND_MAX_VAL + 1);
}

/*
    Заполнение двумерного массива случайными числами
*/
void fillRandomMatrix(int arr[][config::MAX_MATRIX_COLS],
                      size_t rows,
                      size_t cols)
{
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            arr[i][j] = config::RAND_MIN_VAL +
                        std::rand() % (config::RAND_MAX_VAL + 1);
}

/*
    ИСПРАВЛЕНО (п.2, п.4):
    Вывод одномерного массива без проверки "последний / не последний"
*/
void printArray(const int arr[], size_t length)
{
    for (size_t i = 0; i + 1 < length; ++i)
        std::cout << arr[i] << ", ";

    std::cout << arr[length - 1] << std::endl;
}

/*
    ИСПРАВЛЕНО (п.4):
    Вывод двумерного массива
*/
void printMatrix(const int arr[][config::MAX_MATRIX_COLS],
                 size_t rows,
                 size_t cols)
{
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
            std::cout << arr[i][j] << " ";
        std::cout << std::endl;
    }
}

int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    int array[config::MAX_ARRAY_SIZE];
    int matrix[config::MAX_MATRIX_ROWS][config::MAX_MATRIX_COLS];

    size_t arraySize;
    size_t matrixRows;
    size_t matrixCols;

    /*
        ИСПРАВЛЕНО (п.3):
        Для размеров и индексов используется size_t
    */
    std::cout << "Enter array size: ";
    std::cin >> arraySize;

    std::cout << "Enter matrix rows: ";
    std::cin >> matrixRows;

    std::cout << "Enter matrix cols: ";
    std::cin >> matrixCols;

    int left;
    int right;

    std::cout << "Enter left border: ";
    std::cin >> left;

    std::cout << "Enter right border: ";
    std::cin >> right;

    fillRandomArray(array, arraySize);
    fillRandomMatrix(matrix, matrixRows, matrixCols);

    std::cout << "\nArray:" << std::endl;
    printArray(array, arraySize);

    std::cout << "\nMatrix:" << std::endl;
    printMatrix(matrix, matrixRows, matrixCols);

    size_t arrayResult  = countOutOfRangeArray(array, arraySize, left, right);
    size_t matrixResult = countOutOfRangeMatrix(matrix, matrixRows, matrixCols, left, right);

    std::cout << "\nOut-of-range in array: " << arrayResult << std::endl;
    std::cout << "Out-of-range in matrix: " << matrixResult << std::endl;

    return 0;
}
