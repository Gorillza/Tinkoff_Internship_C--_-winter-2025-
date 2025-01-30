#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    long long n;
    std::cin >> n;

    std::vector<long long> budget(n);
    for (long long i = 0; i < n; ++i) {
        std::cin >> budget[i];
    }

    // Предвычисляем все возможные суммы
    std::vector<long long> combinations;
    for (int i = 0; i <= 60; ++i) {
        for (int j = i + 1; j <= 60; ++j) {
            for (int k = j + 1; k <= 60; ++k) {
                long long sum = (1LL << i) + (1LL << j) + (1LL << k);
                combinations.push_back(sum);
            }
        }
    }

    // Сортируем комбинации для быстрого поиска
    std::sort(combinations.begin(), combinations.end());

    // Для каждого бюджета ищем максимально подходящую сумму
    for (long long i = 0; i < n; ++i) {
        auto it = std::upper_bound(combinations.begin(), combinations.end(), budget[i]);
        if (it == combinations.begin()) {
            // Если нет подходящих комбинаций
            std::cout << -1 << std::endl;
        } else {
            // Возвращаем максимально допустимую сумму
            std::cout << *(--it) << std::endl;
        }
    }

    return 0;
}
