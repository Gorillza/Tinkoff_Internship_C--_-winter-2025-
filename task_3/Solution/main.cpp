#include <iostream>
#include <vector>
#include <algorithm>

// Основная функция
int calculateAdjustments(int n, int m, const std::vector<int>& arr) {
    // Создаём отсортированный массив без первых двух элементов (они используются для a1 и a2)
    std::vector<int> sortedArr(arr.begin() + 2, arr.end());
    std::sort(sortedArr.begin(), sortedArr.end());

    int a1 = arr[0]; // Левая граница диапазона
    int a2 = arr[1]; // Правая граница диапазона
    int adjustments = 0;

    // Итераторы для поиска элементов вне диапазона
    auto lower = std::lower_bound(sortedArr.begin(), sortedArr.end(), a1);
    auto upper = std::upper_bound(sortedArr.begin(), sortedArr.end(), a2);

    while (upper - lower < m) {
        // Вычисляем минимальные изменения
        int increaseCost = (upper != sortedArr.end()) ? abs(*upper - a2) : INT_MAX;
        int decreaseCost = (lower != sortedArr.begin()) ? abs(a1 - *(--lower)) : INT_MAX;

        // Подсчитываем, сколько новых элементов попадет в диапазон
        int newElementsByIncreasing = (upper != sortedArr.end()) ? next(upper) - upper : 0;
        int newElementsByDecreasing = (lower != sortedArr.begin()) ? lower - prev(lower)+1 : 0;


        // Выбираем лучшее изменение (наибольшее количество новых элементов за наименьшую стоимость)
        if ((newElementsByIncreasing > newElementsByDecreasing) || 
            (newElementsByIncreasing == newElementsByDecreasing && increaseCost <= decreaseCost)) {
            adjustments += increaseCost;
            a2 += increaseCost;
            upper = next(upper); // Обновляем верхний итератор
        } else {
            adjustments += decreaseCost;
            a1 -= decreaseCost;
            lower = prev(lower); // Обновляем нижний итератор
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
