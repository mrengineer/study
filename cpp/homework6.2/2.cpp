#include <iostream>
#include <utility>

bool isColumnAllPositive(const int** matrix, size_t rows, size_t col);
int** removeAllPositiveColumns(const int** matrix, size_t rows, size_t cols, size_t& newCols);
void printMatrix(const int** matrix, size_t rows, size_t cols);
void deleteMatrix(int** matrix, size_t rows);

int main() 
{
    size_t rows, cols;
    
    std::cout << "Enter number of rows: ";
    std::cin >> rows;
    std::cout << "Enter number of columns: ";
    std::cin >> cols;
    
    if (rows == 0 || cols == 0) 
    {
        std::cout << "Matrix dimensions must be greater than 0" << std::endl;
        return 1;
    }
    
    // Создаем матрицу
    int** matrix = new int*[rows];
    for (size_t i = 0; i < rows; ++i) 
    {
        matrix[i] = new int[cols];
    }
    
    std::cout << "Enter matrix elements:" << std::endl;
    for (size_t i = 0; i < rows; ++i) 
    {
        for (size_t j = 0; j < cols; ++j) 
        {
            std::cout << "Element [" << i << "][" << j << "]: ";
            std::cin >> matrix[i][j];
        }
    }
    
    std::cout << "\nOriginal matrix:" << std::endl;
    printMatrix(const_cast<const int**>(matrix), rows, cols);
    
    size_t newCols;
    int** resultMatrix = removeAllPositiveColumns(const_cast<const int**>(matrix), rows, cols, newCols);
    
    std::cout << "\nMatrix after removing columns with all positive elements:" << std::endl;
    if (newCols > 0) 
    {
        printMatrix(const_cast<const int**>(resultMatrix), rows, newCols);
    } 
    else 
    {
        std::cout << "All columns were removed" << std::endl;
    }
    
    // Чистка памяти
    deleteMatrix(matrix, rows);
    if (resultMatrix != matrix) 
    {
        deleteMatrix(resultMatrix, rows);
    }
    
    return 0;
}

bool isColumnAllPositive(const int** matrix, size_t rows, size_t col) 
{
    for (size_t i = 0; i < rows; ++i) 
    {
        if (matrix[i][col] <= 0) 
        {
            return false;
        }
    }
    return true;
}

int** removeAllPositiveColumns(const int** matrix, size_t rows, size_t cols, size_t& newCols) 
{
    // Сколько оставить колонок
    size_t columnsToKeep = 0;
    for (size_t j = 0; j < cols; ++j) 
    {
        if (!isColumnAllPositive(matrix, rows, j)) 
        {
            ++columnsToKeep;
        }
    }
    
    newCols = columnsToKeep;
    
    if (newCols == 0) 
    {
        return nullptr;
    }
    
    if (newCols == cols) 
    {
        // Ничего не надо удалять
        int** result = new int*[rows];
        for (size_t i = 0; i < rows; ++i) 
        {
            result[i] = new int[newCols];
            for (size_t j = 0; j < newCols; ++j) 
            {
                result[i][j] = matrix[i][j];
            }
        }
        return result;
    }
    
    // Новая матрица у убранными колонками
    int** resultMatrix = new int*[rows];
    for (size_t i = 0; i < rows; ++i) 
    {
        resultMatrix[i] = new int[newCols];
    }
    
    // Копируем
    for (size_t j = 0, resultJ = 0; j < cols; ++j) 
    {
        if (!isColumnAllPositive(matrix, rows, j)) 
        {
            for (size_t i = 0; i < rows; ++i) 
            {
                resultMatrix[i][resultJ] = matrix[i][j];
            }
            ++resultJ;
        }
    }
    
    return resultMatrix;
}

void printMatrix(const int** matrix, size_t rows, size_t cols) 
{
    for (size_t i = 0; i < rows; ++i) 
    {
        for (size_t j = 0; j < cols; ++j) 
        {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

void deleteMatrix(int** matrix, size_t rows) 
{
    if (matrix == nullptr) return;
    
    for (size_t i = 0; i < rows; ++i) 
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}