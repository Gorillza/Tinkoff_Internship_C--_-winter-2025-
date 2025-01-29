#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

int calculate_min_operations(const std::vector<int>& arr, int n, int x, int y, int z) {
    int min_ops_x = INT_MAX, min_ops_y = INT_MAX, min_ops_z = INT_MAX;
    int index_x = -1, index_y = -1, index_z = -1;

    // Проходим по массиву и вычисляем минимальные операции для x, y, z
    for (int i = 0; i < n; ++i) {
        int remainder_x = (x - arr[i] % x) % x;
        int remainder_y = (y - arr[i] % y) % y;
        int remainder_z = (z - arr[i] % z) % z;

        // Обновляем минимальные значения
        if (remainder_x < min_ops_x) {
            min_ops_x = remainder_x;
            index_x = i;
        }
        if (remainder_y < min_ops_y) {
            min_ops_y = remainder_y;
            index_y = i;
        }
        if (remainder_z < min_ops_z) {
            min_ops_z = remainder_z;
            index_z = i;
        }
    }

    // Вычисляем минимальные операции с учетом пересечений
    int total_ops = min_ops_x + min_ops_y + min_ops_z;
    if (index_x == index_y && index_y == index_z) {
        total_ops = std::max({min_ops_x, min_ops_y, min_ops_z});
    } else if (index_x == index_y) {
        total_ops = std::max(min_ops_x, min_ops_y) + min_ops_z;
    } else if (index_x == index_z) {
        total_ops = std::max(min_ops_x, min_ops_z) + min_ops_y;
    } else if (index_y == index_z) {
        total_ops = std::max(min_ops_y, min_ops_z) + min_ops_x;
    }

    return total_ops;
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
