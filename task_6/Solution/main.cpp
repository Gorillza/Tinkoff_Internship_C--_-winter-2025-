#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm> // Подключаем для std::max

using namespace std;

// Функция Евклида для нахождения НОД
int Evklid(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int n;
    cin >> n;

    if (n < 3) {
        cout << 0 << endl;
        return 0;
    }

    vector<pair<int, int>> coords(n);
    for (int i = 0; i < n; i++) {
        cin >> coords[i].first >> coords[i].second;
    }

    int L = 1;

    for (int i = 0; i < n; i++) {
        map<pair<int, int>, int> slopesCount;
        int x1 = coords[i].first, y1 = coords[i].second;

        for (int j = 0; j < n; j++) {
            if (i == j) continue;

            int x2 = coords[j].first, y2 = coords[j].second;
            int dx = x2 - x1, dy = y2 - y1;

            if (dx == 0) {
                slopesCount[{0, 1}]++;
            } else {
                int sign = (dx * dy < 0) ? -1 : 1;

                dx = abs(dx);
                dy = abs(dy);
                int g = Evklid(dx, dy);
                dx /= g;
                dy /= g;

                slopesCount[{sign * dy, dx}]++;
            }
        }

        int localMax = 0;
        for (const auto& pair : slopesCount) {
            localMax = max(localMax, pair.second);
        }

        L = max(L, localMax + 1);
    }

    if (static_cast<double>(L) <= static_cast<double>(2 * n) / 3) {
        cout << n / 3 << endl;
    } else {
        cout << n - L << endl;
    }

    return 0;
}
