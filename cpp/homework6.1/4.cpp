#include <iostream>
#include <utility>

const int MAX_SIZE = 10;

void printMatrix(const int matrix[][MAX_SIZE], size_t size);
int findLastEvenInRow(const int row[], size_t size);
void fillEvenNumbersArray(const int matrix[][MAX_SIZE], size_t size, int result[]);

int main() 
{
    int matrix[MAX_SIZE][MAX_SIZE];
    int evenNumbers[MAX_SIZE];
    size_t matrixSize;
    
    std::cout << "Enter matrix size (n x n, n <= " << MAX_SIZE << "): ";
    std::cin >> matrixSize;
    
    if (matrixSize > MAX_SIZE || matrixSize < 1) 
    {
        std::cout << "Invalid size! Size must be between 1 and " << MAX_SIZE << std::endl;
        return 1;
    }
    
    std::cout << "Enter matrix elements:" << std::endl;
    for (size_t i = 0; i < matrixSize; ++i) 
    {
        for (size_t j = 0; j < matrixSize; ++j) 
        {
            std::cout << "Element [" << i << "][" << j << "]: ";
            std::cin >> matrix[i][j];
        }
    }
    
    std::cout << "\nOriginal matrix:" << std::endl;
    printMatrix(matrix, matrixSize);
    
    fillEvenNumbersArray(matrix, matrixSize, evenNumbers);
    
    std::cout << "\nLast even numbers in each row:" << std::endl;
    for (size_t i = 0; i < matrixSize; ++i) 
    {
        std::cout << "Row " << i << ": ";
        if (evenNumbers[i] != -1) 
        {
            std::cout << evenNumbers[i];
        } 
        else 
        {
            std::cout << "No even number";
        }
        std::cout << std::endl;
    }
    
    return 0;
}

void printMatrix(const int matrix[][MAX_SIZE], size_t size) 
{
    for (size_t i = 0; i < size; ++i) 
    {
        for (size_t j = 0; j < size; ++j) 
        {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

int findLastEvenInRow(const int row[], size_t size) 
{
    int lastEven = -1;
    
    for (size_t j = 0; j < size; ++j) 
    {
        if (row[j] % 2 == 0) 
        {
            lastEven = row[j];
        }
    }
    
    return lastEven;
}

void fillEvenNumbersArray(const int matrix[][MAX_SIZE], size_t size, int result[]) 
{
    for (size_t i = 0; i < size; ++i) 
    {
        result[i] = findLastEvenInRow(matrix[i], size);
    }
}