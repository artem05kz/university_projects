#include <cmath>
#include <iostream>

// Функция для вычисления cos(x) рекурсивно
double cos_recursive(double x, double epsilon, int n = 0, double term = 1) {
    if (std::abs(term) < epsilon) {
        return 0;
    }
    return term + cos_recursive(x, epsilon, n + 1, -term * x * x / ((2 * n + 2) * (2 * n + 1)));
}

int main() {
    double x = 5.0;  // значение для которого нужно вычислить cos(x)
    double epsilon = 1e-6;  // точность
    std::cout << "cos(" << x << ") = " << cos_recursive(x, epsilon) << std::endl;
    return 0;
}
