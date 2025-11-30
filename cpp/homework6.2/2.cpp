#include <iostream>
#include <limits> // для std::numeric_limits

bool isColumnAllPositive(const int** matrix, size_t rows, size_t col);
int** removeAllPositiveColumns(const int** matrix, size_t rows, size_t cols, size_t& newCols);
void printMatrix(const int** matrix, size_t rows, size_t cols);
void deleteMatrix(int** matrix, size_t rows);

// <<< EDIT: helper для создания матрицы вынесен (чтобы избежать дублирования) >>>
int** createMatrix(size_t rows, size_t cols)
{
    // <<< EDIT: проверка на нулевые размеры >>>
    if (rows == 0 || cols == 0) return nullptr;

    int** m = nullptr;
    try {
        m = new int*[rows];
        for (size_t i = 0; i < rows; ++i) {
            m[i] = new int[cols];
        }
    } catch (const std::bad_alloc&) {
        // <<< EDIT: в случае неудачи — чистим уже выделенное и возвращаем nullptr >>>
        if (m) {
            for (size_t i = 0; i < rows; ++i) {
                // Если часть строк ещё не выделена, проверка нужна
                if (m[i]) delete[] m[i];
            }
            delete[] m;
        }
        return nullptr;
    }
    return m;
}

int main() 
{
    size_t rows = 0, cols = 0;
    
    std::cout << "Enter number of rows: ";
    if (!(std::cin >> rows)) { // <<< EDIT: проверка ввода >>>
        std::cerr << "Invalid input for rows\n";
        return 1;
    }
    std::cout << "Enter number of columns: ";
    if (!(std::cin >> cols)) { // <<< EDIT: проверка ввода >>>
        std::cerr << "Invalid input for columns\n";
        return 1;
    }
    
    if (rows == 0 || cols == 0) 
    {
        std::cout << "Matrix dimensions must be greater than 0" << std::endl;
        return 1;
    }
    
    // Создаем матрицу
    int** matrix = createMatrix(rows, cols); // <<< EDIT: используем createMatrix >>>
    if (matrix == nullptr) { // <<< EDIT: проверка успешности выделения >>>
        std::cerr << "Memory allocation failed for matrix\n";
        return 1;
    }
    
    std::cout << "Enter matrix elements:" << std::endl;
    for (size_t i = 0; i < rows; ++i) 
    {
        for (size_t j = 0; j < cols; ++j) 
        {
            std::cout << "Element [" << i << "][" << j << "]: ";
            if (!(std::cin >> matrix[i][j])) { // <<< EDIT: проверка ввода элемента >>>
                std::cerr << "Invalid input for element [" << i << "][" << j << "]\n";
                // очищаем и выходим
                deleteMatrix(matrix, rows);
                return 1;
            }
        }
    }
    
    std::cout << "\nOriginal matrix:" << std::endl;
    printMatrix(const_cast<const int**>(matrix), rows, cols);
    
    size_t newCols = 0;
    int** resultMatrix = removeAllPositiveColumns(const_cast<const int**>(matrix), rows, cols, newCols);
    
    std::cout << "\nMatrix after removing columns with all positive elements:" << std::endl;
    if (newCols > 0 && resultMatrix != nullptr) 
    {
        printMatrix(const_cast<const int**>(resultMatrix), rows, newCols);
    } 
    else 
    {
        std::cout << "All columns were removed" << std::endl;
    }
    
    // Чистка памяти
    // <<< EDIT: освобождаем старую матрицу всегда >>>
    deleteMatrix(matrix, rows);

    // <<< EDIT: если resultMatrix есть и это не тот же указатель, который уже удалён, удаляем >>>
    // В нашей реализации resultMatrix никогда равен исходному matrix, но оставим проверку на всякий случай
    if (resultMatrix != nullptr && resultMatrix != matrix) 
    {
        deleteMatrix(resultMatrix, rows);
    }
    
    return 0;
}

bool isColumnAllPositive(const int** matrix, size_t rows, size_t col) 
{
    // <<< EDIT: защита от некорректных указателей и индекса столбца >>>
    if (matrix == nullptr) return false; // если нет матрицы, считать, что столбец не "весь положительный"
    // rows может быть 0 — тогда столбец не считается "весь положительный"
    if (rows == 0) return false;

    for (size_t i = 0; i < rows; ++i) 
    {
        // <<< EDIT: защита от некорректной строки >>>
        if (matrix[i] == nullptr) return false;
        if (matrix[i][col] <= 0) 
        {
            return false;
        }
    }
    return true;
}

int** removeAllPositiveColumns(const int** matrix, size_t rows, size_t cols, size_t& newCols) 
{
    newCols = 0;

    // <<< EDIT: защита входных параметров >>>
    if (matrix == nullptr || rows == 0 || cols == 0) 
    {
        return nullptr;
    }

    // Сколько оставить колонок
    for (size_t j = 0; j < cols; ++j) 
    {
        if (!isColumnAllPositive(matrix, rows, j)) 
        {
            ++newCols;
        }
    }
    
    if (newCols == 0) 
    {
        return nullptr;
    }
    
    // <<< EDIT: используем одну функцию создания матрицы вместо дублирования кода >>>
    int** resultMatrix = createMatrix(rows, newCols);
    if (resultMatrix == nullptr) { // <<< EDIT: проверка успешности выделения >>>
        std::cerr << "Memory allocation failed for result matrix\n";
        newCols = 0;
        return nullptr;
    }
    
    // Копируем
    for (size_t j = 0, resultJ = 0; j < cols; ++j) 
    {
        if (!isColumnAllPositive(matrix, rows, j)) 
        {
            for (size_t i = 0; i < rows; ++i) 
            {
                // <<< EDIT: защита от nullptr строк источника >>>
                if (matrix[i] == nullptr) {
                    // аварийная ситуация — очищаем уже выделенное и возвращаем nullptr
                    deleteMatrix(resultMatrix, rows);
                    newCols = 0;
                    return nullptr;
                }
                resultMatrix[i][resultJ] = matrix[i][j];
            }
            ++resultJ;
        }
    }
    
    return resultMatrix;
}

void printMatrix(const int** matrix, size_t rows, size_t cols) 
{
    if (matrix == nullptr) {
        std::cout << "(empty matrix)\n";
        return;
    }

    for (size_t i = 0; i < rows; ++i) 
    {
        if (matrix[i] == nullptr) {
            // защита: если какая-то строка отсутствует, выводим маркер
            for (size_t j = 0; j < cols; ++j) std::cout << "?\t";
            std::cout << std::endl;
            continue;
        }

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
        // <<< EDIT: защита от удаления незаполненной строки >>>
        if (matrix[i] != nullptr) delete[] matrix[i];
    }
    delete[] matrix;
}
