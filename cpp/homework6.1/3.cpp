#include <iostream>

/*
    ИСПРАВЛЕНО (п.1):
    Глобальная константа перенесена в пространство имён
*/
namespace config
{
    const size_t MAX_MATRIX_SIZE = 10;
}

/*
    Умножение двух квадратных матриц размера n x n
*/
void multiplyMatrices(const int a[][config::MAX_MATRIX_SIZE],
                      const int b[][config::MAX_MATRIX_SIZE],
                      int result[][config::MAX_MATRIX_SIZE],
                      size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            result[i][j] = 0;
            for (size_t k = 0; k < n; ++k)
                result[i][j] += a[i][k] * b[k][j];
        }
    }
}

/*
    ИСПРАВЛЕНО (п.4):
    Вывод матрицы для проверки
*/
void printMatrix(const int matrix[][config::MAX_MATRIX_SIZE], size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
            std::cout << matrix[i][j] << "\t";
        std::cout << std::endl;
    }
}

int main()
{
    int matrix[config::MAX_MATRIX_SIZE][config::MAX_MATRIX_SIZE];
    int result[config::MAX_MATRIX_SIZE][config::MAX_MATRIX_SIZE];
    int temp[config::MAX_MATRIX_SIZE][config::MAX_MATRIX_SIZE];

    /*
        ИСПРАВЛЕНО (п.3):
        Для размеров и индексов используется size_t
    */
    size_t n;
    size_t power;

    std::cout << "Enter matrix size (1-" << config::MAX_MATRIX_SIZE << "): ";
    std::cin >> n;

    if (n == 0 || n > config::MAX_MATRIX_SIZE)
    {
        std::cout << "Error: invalid matrix size" << std::endl;
        return 1;
    }

    std::cout << "Enter power: ";
    std::cin >> power;

    std::cout << "Enter matrix elements:" << std::endl;
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < n; ++j)
        {
            std::cout << "Element [" << i << "][" << j << "]: ";
            std::cin >> matrix[i][j];
        }

    std::cout << "\nOriginal matrix:" << std::endl;
    printMatrix(matrix, n);

    /*
        Если степень равна 0 — единичная матрица
    */
    if (power == 0)
    {
        for (size_t i = 0; i < n; ++i)
            for (size_t j = 0; j < n; ++j)
                result[i][j] = (i == j) ? 1 : 0;
    }
    else
    {
        /*
            Начальное значение result = matrix
        */
        for (size_t i = 0; i < n; ++i)
            for (size_t j = 0; j < n; ++j)
                result[i][j] = matrix[i][j];

        /*
            ИСПРАВЛЕНО (п.2):
            Нет проверок "последний / не последний",
            цикл выполняется power - 1 раз
        */
        for (size_t p = 1; p < power; ++p)
        {
            multiplyMatrices(result, matrix, temp, n);

            for (size_t i = 0; i < n; ++i)
                for (size_t j = 0; j < n; ++j)
                    result[i][j] = temp[i][j];
        }
    }

    std::cout << "\nMatrix to power " << power << ":" << std::endl;
    printMatrix(result, n);

    return 0;
}
