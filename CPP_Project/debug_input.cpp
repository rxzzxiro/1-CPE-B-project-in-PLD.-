#include <iostream>
#include <string>

int main() {
    std::string s;
    while (std::getline(std::cin, s)) {
        std::cout << "[READ] " << s << "\n";
    }
    std::cout << "[END OF INPUT]\n";
    return 0;
}
