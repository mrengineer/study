#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    double a, b, c;
    cout << "Введите коэффициенты a, b, c: ";
    cin >> a >> b >> c;

    double D = b * b - 4 * a * c;

    cout << fixed << setprecision(2);

    if (D > 0)
        cout << "Уравнение имеет два решения (D = " << D << ")" << endl;
    else if (D == 0)
        cout << "Уравнение имеет одно решение (D = " << D << ")" << endl;
    else
        cout << "Уравнение не имеет действительных решений (D = " << D << ")" << endl;

    return 0;
}
