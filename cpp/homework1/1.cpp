#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    double x, y;

    cout << "Введите x: ";
    cin >> x;
    cout << "Введите y: ";
    cin >> y;

    double result = ((x + y) / (x + 1)) - ((x * y - 12) / (34 + x));

    cout << fixed << setprecision(4); // 4 знака после запятой
    cout << "Результат выражения = " << setw(10) << result << endl;

    return 0;
}
