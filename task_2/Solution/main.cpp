#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

int main() {
    long long n;
    std::cin >> n;

    std::vector<long long> budget(n);
    for (long long i = 0; i < n; ++i) {
        std::cin >> budget[i];
    }

    // Минимальная стоимость букета из 3 цветов: 2^0 + 2^1 + 2^2 = 7
    const long long min_cost = 7;

    for (long long i = 0; i < n; ++i) {
        if (budget[i] < min_cost) {
            std::cout << -1 << std::endl; // Невозможно купить букет
        } else {
            // Находим три самых дорогих цветка, которые можно купить
            long long remaining_budget = budget[i];
            std::vector<long long> selected_flowers;

            for (long long power = 60; power >= 0 && selected_flowers.size() < 3; --power) {
                long long cost = 1LL << power; // Стоимость цветка
                if (remaining_budget >= cost) {
                    selected_flowers.push_back(cost);
                    remaining_budget -= cost;
                }
            }

            // Если удалось выбрать ровно три цветка, то выводим их стоимость
            if (selected_flowers.size() == 3) {
                long long total_cost = selected_flowers[0] + selected_flowers[1] + selected_flowers[2];
                std::cout << total_cost << std::endl;
            } else {
                std::cout << -1 << std::endl; // Не удалось выбрать три цветка
            }
        }
    }

    return 0;
}
