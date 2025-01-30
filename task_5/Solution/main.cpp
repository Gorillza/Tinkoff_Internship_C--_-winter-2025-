#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    long long s;
    cin >> n >> s;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // Префиксные суммы
    vector<long long> prefixSum(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        prefixSum[i + 1] = prefixSum[i] + a[i];
    }

    long long totalSum = 0;

    // Подсчёт всех подотрезков
    for (int l = 0; l < n; ++l) {
        for (int r = l; r < n; ++r) {
            // Сумма подотрезка [l, r]
            long long segmentSum = prefixSum[r + 1] - prefixSum[l];
            // Количество частей для подотрезка
            totalSum += (segmentSum + s - 1) / s; // Округление вверх
        }
    }

    cout << totalSum << endl;

    return 0;
}
