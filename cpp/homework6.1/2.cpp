#include <iostream>
#include <iomanip>

const int MAX_ARRAY_SIZE = 100;

int main() {
    double array[MAX_ARRAY_SIZE];
    int n;
    
    std::cout << "Enter array size (1-" << MAX_ARRAY_SIZE << "): ";
    std::cin >> n;
    
    if (n <= 0 || n > MAX_ARRAY_SIZE) {
        std::cout << "Error: array size must be between 1 and " << MAX_ARRAY_SIZE << std::endl;
        return 1;
    }
    
    std::cout << "Enter " << n << " real numbers:" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "Element " << i << ": ";
        std::cin >> array[i];
    }
    
    std::cout << "Array elements: ";
    for (int i = 0; i < n; i++) {
        std::cout << std::fixed << std::setprecision(2) << array[i];
        if (i < n - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    
    double min_value = array[0];
    int last_min_index = 0;
    
    for (int i = 1; i < n; i++) {
        if (array[i] <= min_value) {
            min_value = array[i];
            last_min_index = i;
        }
    }
    
    std::cout << "Last minimum element index: " << last_min_index << std::endl;
    std::cout << "Value: " << std::fixed << std::setprecision(2) << array[last_min_index] << std::endl;
    
    return 0;
}