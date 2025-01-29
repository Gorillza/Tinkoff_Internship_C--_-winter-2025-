#include <iostream>
#include <vector>
#include <algorithm>

int calculateAdjustments(int totalDays, int requiredGoodDays, std::vector<int>& distances) {
    int currentGoodDays = 0;

    // Подсчитываем количество "хороших" дней
    for (int index = 2; index < totalDays; index++) {
        if (distances[index] >= distances[0] && distances[index] <= distances[1]) {
            currentGoodDays++;
        }
    }

    // Если уже достаточно "хороших" дней, возвращаем 0
    if (currentGoodDays >= requiredGoodDays) {
        return 0;
    }

    // Собираем дни, которые не соответствуют условию
    std::vector<int> invalidDays;
    for (int index = 2; index < totalDays; index++) {
        if (!(distances[index] >= distances[0] && distances[index] <= distances[1])) {
            invalidDays.push_back(distances[index]);
        }
    }

    // Сортируем "неправильные" дни
    std::sort(invalidDays.begin(), invalidDays.end());

    int totalAdjustments = 0;
    // Корректируем "неправильные" дни, чтобы они стали "хорошими"
    for (size_t idx = 0; idx < invalidDays.size() && currentGoodDays < requiredGoodDays; idx++) {
        if (invalidDays[idx] < distances[0]) {
            totalAdjustments += distances[0] - invalidDays[idx];
        } else if (invalidDays[idx] > distances[1]) {
            totalAdjustments += invalidDays[idx] - distances[1];
        }
        currentGoodDays++;
    }

    return totalAdjustments;
}

int main() {
    int totalDays, minGoodDays;
    std::cin >> totalDays >> minGoodDays;

    std::vector<int> runDistances(totalDays);
    for (int day = 0; day < totalDays; day++) {
        std::cin >> runDistances[day];
    }

    int result = calculateAdjustments(totalDays, minGoodDays, runDistances);
    std::cout << result << std::endl;

    return 0;
}
