#include <bits/stdc++.h>


int main() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::stringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d");
    std::cout <<ss.str() << std::endl;
    return 0;
}
