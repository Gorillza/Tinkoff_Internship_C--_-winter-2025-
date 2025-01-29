#include <iostream>
#include <vector>
using namespace std;

const long long MOD = 998244353;

// Быстрое возведение в степень
long long QuickPow(long long value, long long pow, long long mod) {
    long long result = 1, temp = value;
    while (pow != 0) {
        if (pow % 2 == 1) {
            result = (result * temp) % mod;
        }
        temp = (temp * temp) % mod;
        pow /= 2;
    }
    return result;
}

// Вычисление биномиальных коэффициентов C(p, m)
vector<long long> Cnk(long long p) {
    vector<long long> coefficients(p + 1, 0);
    coefficients[0] = 1;
    for (long long i = 1; i <= p; ++i) {
        coefficients[i] = (coefficients[i - 1] * (p - i + 1) / i) % MOD;
    }
    return coefficients;
}

// Вычисление сумм S_m
vector<long long> Sums(vector<long long> array, int k) {
    vector<long long> temp = array; // Создаем копию массива
    vector<long long> result(k + 1, 0);
    result[0] = array.size();
    for (int i = 1; i <= k; ++i) {
        long long sum = 0;
        for (size_t j = 0; j < array.size(); ++j) {
            sum = (sum + array[j]) % MOD;
            array[j] = (array[j] * temp[j]) % MOD; // Изменяем копию массива
        }
        result[i] = sum % MOD;
    }
    return result;
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<long long> array(n);
    for (int i = 0; i < n; i++) {
        cin >> array[i];
    }

    vector<long long> sums = Sums(array, k);

    for (int p = 1; p <= k; ++p) {
        vector<long long> cnk = Cnk(p);
        long long f = 0;

        for (int m = 0; m <= p; ++m) {
            f = (f + cnk[m] * (sums[m] * sums[p - m] % MOD - sums[p]) / 2) % MOD;
        }

        cout << f << endl;
    }

    return 0;
}
