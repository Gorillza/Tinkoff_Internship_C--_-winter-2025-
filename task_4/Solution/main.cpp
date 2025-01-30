#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;
using ull = unsigned long long;

// Функция для вычисления НОД
ull GCD(ull a, ull b) {
    while (b != 0) {
        ull t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Функция для вычисления НОК
ull LCM(ull a, ull b) {
    return a * (b / GCD(a, b));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ull x, y, z;
    cin >> n >> x >> y >> z;

    // Вычисляем все НОК
    ull xy = LCM(x, y);
    ull xz = LCM(x, z);
    ull yz = LCM(y, z);
    ull xyz = LCM(LCM(x, y), z);

    // Векторы для хранения количества изменений
    vector<ull> c_xyz(n, 0), c_xy(n, 0), c_xz(n, 0);
    vector<ull> c_yz(n, 0), c_x(n, 0), c_y(n, 0), c_z(n, 0);

    // Читаем входные данные и заполняем массивы изменений
    for (int i = 0; i < n; i++) {
        ull a;
        cin >> a;
        if (a % xyz != 0) c_xyz[i] = xyz - a % xyz;
        if (a % xy != 0) c_xy[i] = xy - a % xy;
        if (a % xz != 0) c_xz[i] = xz - a % xz;
        if (a % yz != 0) c_yz[i] = yz - a % yz;
        if (a % x != 0) c_x[i] = x - a % x;
        if (a % y != 0) c_y[i] = y - a % y;
        if (a % z != 0) c_z[i] = z - a % z;
    }

    // Инициализируем минимальное значение преобразования
    ull best = *min_element(c_xyz.begin(), c_xyz.end());

    // Если n == 1, сразу выводим результат
    if (n == 1) {
        cout << best << "\n";
        return 0;
    }

    // Создаем массивы для двухкратных и однократных делений
    vector<vector<ull>> c_p_vars = {c_xy, c_xz, c_yz};
    vector<vector<ull>> c_t_vars = {c_z, c_y, c_x};

    // Проверяем комбинации двух чисел (одно кратно двум, другое — одному)
    for (int i = 0; i < 3; i++) {
        vector<ull>& c_p = c_p_vars[i];
        vector<ull>& c_t = c_t_vars[i];

        pair<int, int> best_p = {-1, -1};
        pair<int, int> best_t = {-1, -1};

        // Поиск двух наименьших значений
        for (int j = 0; j < n; j++) {
            if (best_p.first == -1 || c_p[j] <= c_p[best_p.first]) {
                best_p.second = best_p.first;
                best_p.first = j;
            } else if (best_p.second == -1 || c_p[j] <= c_p[best_p.second]) {
                best_p.second = j;
            }

            if (best_t.first == -1 || c_t[j] <= c_t[best_t.first]) {
                best_t.second = best_t.first;
                best_t.first = j;
            } else if (best_t.second == -1 || c_t[j] <= c_t[best_t.second]) {
                best_t.second = j;
            }
        }

        // Проверяем комбинации из двух чисел
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                if (best_p.first == best_t.second) continue;
                ull c = c_p[best_p.first] + c_t[best_t.second];
                best = min(best, c);
            }
        }
    }

    // Если n == 2, сразу выводим результат
    if (n == 2) {
        cout << best << "\n";
        return 0;
    }

    // Поиск трех различных минимальных значений
    vector<vector<int>> best_t(3, vector<int>(3, -1));

    for (int i = 0; i < 3; i++) {
        vector<ull>& c_t = c_t_vars[i];

        for (int j = 0; j < n; j++) {
            if (best_t[i][0] == -1 || c_t[j] <= c_t[best_t[i][0]]) {
                best_t[i][2] = best_t[i][1];
                best_t[i][1] = best_t[i][0];
                best_t[i][0] = j;
            } else if (best_t[i][1] == -1 || c_t[j] <= c_t[best_t[i][1]]) {
                best_t[i][2] = best_t[i][1];
                best_t[i][1] = j;
            } else if (best_t[i][2] == -1 || c_t[j] <= c_t[best_t[i][2]]) {
                best_t[i][2] = j;
            }
        }
    }

    // Проверяем все возможные комбинации из трех разных индексов
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                int i_z = best_t[0][i];
                int i_y = best_t[1][j];
                int i_x = best_t[2][k];

                if (i_x == i_y || i_x == i_z || i_y == i_z) continue;

                ull c = c_x[i_x] + c_y[i_y] + c_z[i_z];
                best = min(best, c);
            }
        }
    }

    cout << best << "\n";
    return 0;
}
