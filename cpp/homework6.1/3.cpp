#include <iostream>

const int MAX_MATRIX_SIZE = 10;

int main() {
    int matrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
    int result[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
    int temp[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
    
    int n;
    int power;
    
    std::cout << "Enter matrix size (1-" << MAX_MATRIX_SIZE << "): ";
    std::cin >> n;
    
    if (n <= 0 || n > MAX_MATRIX_SIZE) {
        std::cout << "Error: matrix size must be between 1 and " << MAX_MATRIX_SIZE << std::endl;
        return 1;
    }
    
    std::cout << "Enter power: ";
    std::cin >> power;
    
    if (power < 0) {
        std::cout << "Error: power must be non-negative" << std::endl;
        return 1;
    }
    
    std::cout << "Enter matrix elements:" << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << "Element [" << i << "][" << j << "]: ";
            std::cin >> matrix[i][j];
        }
    }
    
    std::cout << "Original matrix:" << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    
    if (power == 0) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                result[i][j] = (i == j) ? 1 : 0;
            }
        }
    } else {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                result[i][j] = matrix[i][j];
            }
        }
        
        for (int p = 1; p < power; p++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    temp[i][j] = 0;
                    for (int k = 0; k < n; k++) {
                        temp[i][j] += result[i][k] * matrix[k][j];
                    }
                }
            }
            
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    result[i][j] = temp[i][j];
                }
            }
        }
    }
    
    std::cout << "Matrix to power " << power << ":" << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << result[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    
    return 0;
}