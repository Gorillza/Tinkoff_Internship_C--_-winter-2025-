#include <iostream>
#include <vector>
#include <cmath>

int main() {
    int n;
    long long s;
    std::cin >> n >> s;

    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    // Построение префиксной суммы
    std::vector<long long> prefixSum(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        prefixSum[i + 1] = prefixSum[i] + a[i];
    }

    long long totalSum = 0;

    // Обработка всех подотрезков
    for (int l = 0; l < n; ++l) {
        for (int r = l; r < n; ++r) {
            // Вычисляем длину подотрезка [l, r] через префиксную сумму
            long long segmentLength = prefixSum[r + 1] - prefixSum[l];
            // Добавляем количество частей, необходимых для подотрезка
            totalSum += (segmentLength + s - 1) / s; // Округление вверх
        }
    }

    std::cout << totalSum << std::endl;

    return 0;
}
