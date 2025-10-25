#include <iostream>
#include <iomanip>
#include <cmath>  // для sqrt

using namespace std;

int main() {
    double a, b;

    cout << "Введите катет a: ";
    cin >> a;
    cout << "Введите катет b: ";
    cin >> b;

    double c = sqrt(a * a + b * b);

    cout << fixed << setprecision(3);
    cout << "Гипотенуза = " << setw(8) << c << endl;

    return 0;
}
