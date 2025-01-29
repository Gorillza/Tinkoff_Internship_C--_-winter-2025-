#include <iostream>
#include <vector>

int main() {
    int n;
    long long s;
    std::cin >> n >> s;

    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    long long totalSum = 0;

    // Перебираем все подотрезки
    for (int l = 0; l < n; ++l) {
        for (int r = l; r < n; ++r) {
            long long parts = 0;
            // Считаем количество частей для всех сегментов в текущем подотрезке
            for (int k = l; k <= r; ++k) {
                parts += (a[k] + s - 1) / s; // Округление вверх
            }
            totalSum += parts; // Добавляем к общей сумме
        }
    }

    std::cout << totalSum << std::endl;

    return 0;
}
