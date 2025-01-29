#include <iostream>
#include <vector>

using namespace std;

const int CONST_VALUE = 998244353;

// Функция быстрого возведения в степень по модулю
int PowerMod(int base, int exp, int mod) {
    int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (1LL * result * base) % mod;
        }
        base = (1LL * base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> array(n);
    for (int i = 0; i < n; i++) {
        cin >> array[i];
    }

    vector<int> results(k);

    for (int p = 1; p <= k; p++) {
        vector<int> sums;
        sums.reserve(n * (n - 1) / 2);

        // Генерация всех парных сумм
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                sums.push_back(array[i] + array[j]);
            }
        }

        int totalSum = 0;

        // Вычисление суммы возведенных в степень парных сумм
        for (int v : sums) {
            totalSum = (totalSum + PowerMod(v, p, CONST_VALUE)) % CONST_VALUE;
        }

        results[p - 1] = totalSum;
    }

    // Вывод результатов
    for (int result : results) {
        cout << result << '\n';
    }

    return 0;
}
