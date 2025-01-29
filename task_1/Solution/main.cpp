#include <iostream>
#include <string>

int main() {
    std::string s;
    std::cin >> s;

    // Проверяем порядок символов
    if (s.find('R') < s.find('M')) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }

    return 0;
}
