#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

const size_t MAX_ARRAY_SIZE = 100;
const size_t MAX_MATRIX_ROWS = 10;
const size_t MAX_MATRIX_COLS = 10;
const int RAND_MIN_VAL = 0;
const int RAND_MAX_VAL = 1024;

size_t countOutOfRangeArray(const int values[], 
                           size_t length, 
                           int left, 
                           int right)
{
    size_t count = 0;

    for (size_t i = 0; i < length; i++)
    {
        if (values[i] < left || values[i] > right)
            count++;
    }
    return count;
}

size_t countOutOfRangeMatrix(const int values[][MAX_MATRIX_COLS],
                            size_t rows, 
                            size_t cols, 
                            int left, 
                            int right)
{
    size_t count = 0;

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            if (values[i][j] < left || values[i][j] > right)
                count++;
        }
    }
    return count;
}

void fillRandomArray(int arr[], size_t length)
{
    for (size_t i = 0; i < length; i++)
        arr[i] = RAND_MIN_VAL + std::rand() % (RAND_MAX_VAL + 1);
}

void fillRandomMatrix(int arr[][MAX_MATRIX_COLS], size_t rows, size_t cols)
{
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            arr[i][j] = RAND_MIN_VAL + std::rand() % (RAND_MAX_VAL + 1);
}

int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    int array[MAX_ARRAY_SIZE];
    int matrix[MAX_MATRIX_ROWS][MAX_MATRIX_COLS];

    size_t arraySize;
    size_t matrixRows;
    size_t matrixCols;

    std::cout << "Enter array size (1-" << MAX_ARRAY_SIZE << "): ";
    std::cin >> arraySize;

    if (arraySize == 0 || arraySize > MAX_ARRAY_SIZE)
    {
        std::cout << "Error: array size must be between 1 and " << MAX_ARRAY_SIZE << std::endl;
        return 1;
    }

    std::cout << "Enter matrix rows (1-" << MAX_MATRIX_ROWS << "): ";
    std::cin >> matrixRows;

    if (matrixRows == 0 || matrixRows > MAX_MATRIX_ROWS)
    {
        std::cout << "Error: matrix rows must be between 1 and " << MAX_MATRIX_ROWS << std::endl;
        return 1;
    }

    std::cout << "Enter matrix cols (1-" << MAX_MATRIX_COLS << "): ";
    std::cin >> matrixCols;

    if (matrixCols == 0 || matrixCols > MAX_MATRIX_COLS)
    {
        std::cout << "Error: matrix cols must be between 1 and " << MAX_MATRIX_COLS << std::endl;
        return 1;
    }

    int left = 0;
    int right = 0;

    std::cout << "Enter left range border: ";
    std::cin >> left;

    std::cout << "Enter right range border: ";
    std::cin >> right;

    if (left > right)
    {
        std::cout << "Error: left border cannot be greater than right border" << std::endl;
        return 1;
    }

    fillRandomArray(array, arraySize);
    fillRandomMatrix(matrix, matrixRows, matrixCols);

    size_t arrayResult = countOutOfRangeArray(array, arraySize, left, right);
    size_t matrixResult = countOutOfRangeMatrix(matrix, matrixRows, matrixCols, left, right);

    std::cout << "\nGenerated array (" << arraySize << " elements)" << std::endl;
    std::cout << "Out-of-range count: " << arrayResult << std::endl;

    std::cout << "\nGenerated matrix (" << matrixRows << "x" << matrixCols << ")" << std::endl;
    std::cout << "Out-of-range count: " << matrixResult << std::endl;

    return 0;
}