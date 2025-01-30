#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <climits>

// Структура для хранения остатка и индекса
struct Remainder {
    int value;
    int index;
};

// Функция для вычисления минимальных операций
int calculate_min_operations(const std::vector<int>& arr, int n, int x, int y, int z) {
    int min_operations = INT_MAX;

    // Вектора для остатков
    std::vector<Remainder> remainders_x(n), remainders_y(n), remainders_z(n);

    // Вычисляем остатки для каждого делителя
    for (int i = 0; i < n; ++i) {
        remainders_x[i] = { (x - arr[i] % x) % x, i };
        remainders_y[i] = { (y - arr[i] % y) % y, i };
        remainders_z[i] = { (z - arr[i] % z) % z, i };
    }

    // Сортируем остатки для каждого делителя
    auto sort_by_value = [](const Remainder& a, const Remainder& b) {
        return a.value < b.value;
    };
    std::sort(remainders_x.begin(), remainders_x.end(), sort_by_value);
    std::sort(remainders_y.begin(), remainders_y.end(), sort_by_value);
    std::sort(remainders_z.begin(), remainders_z.end(), sort_by_value);

    // Перебираем все возможные комбинации
    for (const auto& rem_x : remainders_x) {
        for (const auto& rem_y : remainders_y) {
            for (const auto& rem_z : remainders_z) {
                // Если все три остатка относятся к одному числу
                if (rem_x.index == rem_y.index && rem_y.index == rem_z.index) {
                    min_operations = std::min(min_operations, rem_x.value + rem_y.value + rem_z.value);
                }
                // Если два числа совпадают
                else if (rem_x.index == rem_y.index) {
                    min_operations = std::min(min_operations, rem_x.value + rem_y.value + rem_z.value);
                } else if (rem_y.index == rem_z.index) {
                    min_operations = std::min(min_operations, rem_x.value + rem_y.value + rem_z.value);
                } else if (rem_x.index == rem_z.index) {
                    min_operations = std::min(min_operations, rem_x.value + rem_y.value + rem_z.value);
                }
                // Если все числа разные
                else {
                    min_operations = std::min(min_operations, rem_x.value + rem_y.value + rem_z.value);
                }
            }
        }
    }

    return min_operations;
}

int main() {
    int n, x, y, z;
    std::cin >> n >> x >> y >> z;

    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    int result = calculate_min_operations(arr, n, x, y, z);
    std::cout << result << std::endl;

    return 0;
}
