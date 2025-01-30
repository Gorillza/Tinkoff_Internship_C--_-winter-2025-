#include <iostream>
#include <vector>
#include <algorithm>

// Функция подсчёта количества элементов в диапазоне [a1, a2]
int countInRange(const std::vector<int>& sortedArr, int a1, int a2) {
    auto lower = std::lower_bound(sortedArr.begin(), sortedArr.end(), a1);
    auto upper = std::upper_bound(sortedArr.begin(), sortedArr.end(), a2);
    return upper - lower;
}

// Основная функция
int calculateAdjustments(int n, int m, const std::vector<int>& arr) {
    // Создаём отсортированный массив
    std::vector<int> sortedArr = arr;
    sortedArr.erase(sortedArr.begin());
    sortedArr.erase(sortedArr.begin());
    std::sort(sortedArr.begin(), sortedArr.end());

    int a1 = arr[0];
    int a2 = arr[1];
    int adjustments = 0;

    while (countInRange(sortedArr, a1, a2) < m) {
        // Находим ближайшие элементы вне диапазона
        auto upper = std::upper_bound(sortedArr.begin(), sortedArr.end(), a2);
        auto lower = std::lower_bound(sortedArr.begin(), sortedArr.end(), a1);

        // Вычисляем минимальные изменения
        int increaseCost = (upper != sortedArr.end()) ? abs(*upper - a2) : INT_MAX;
        int decreaseCost = (lower != sortedArr.begin()) ? abs(a1 - *(--lower)) : INT_MAX;

        // Подсчитываем, сколько новых элементов попадет в диапазон
        int newElementsByIncreasing = (upper != sortedArr.end()) ? std::upper_bound(sortedArr.begin(), sortedArr.end(), a2 + increaseCost) - upper : 0;
        int newElementsByDecreasing = (lower != sortedArr.begin()) ? lower - std::lower_bound(sortedArr.begin(), sortedArr.end(), a1 - decreaseCost) + 1 : 0;

        // Выбираем лучшее изменение (наибольшее количество новых элементов за наименьшую стоимость)
        if ((newElementsByIncreasing > newElementsByDecreasing) || 
            (newElementsByIncreasing == newElementsByDecreasing && increaseCost <= decreaseCost)) {
            adjustments += increaseCost;
            a2 += increaseCost; // Увеличиваем правую границу
        } else {
            adjustments += decreaseCost;
            a1 -= decreaseCost; // Уменьшаем левую границу
        }
    }

    return adjustments;
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    int result = calculateAdjustments(n, m, arr);
    std::cout << result << std::endl;

    return 0;
}
