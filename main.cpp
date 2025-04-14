#include <iostream>
#include "IPv4PrefixSet.h"

std::string ipToString(uint32_t ip) {
    return std::to_string((ip >> 24) & 0xFF) + "." +
           std::to_string((ip >> 16) & 0xFF) + "." +
           std::to_string((ip >> 8) & 0xFF) + "." +
           std::to_string(ip & 0xFF);
}

int main() {
    IPv4PrefixSet prefixSet;

    uint32_t ip1 = (192 << 24) | (168 << 16) | (1 << 8) | 0;  // 192.168.1.0
    uint32_t ip2 = (10 << 24) | (0 << 16) | (0 << 8) | 0;     // 10.0.0.0

    std::cout << "Adding prefixes:" << std::endl;
    if (prefixSet.add(ip1, 24)) {
        std::cout << "Added: " << ipToString(ip1) << "/24" << std::endl;
    }

    std::cout << "Adding prefixes (second time):" << std::endl;
    if (prefixSet.add(ip1, 26)) {
        std::cout << "Added: " << ipToString(ip1) << "/26" << std::endl;
    }

    std::cout << "\nChecking prefix:" << std::endl;
    int result = prefixSet.check(ip1);
    std::cout << "Check result: " << result << std::endl;

    return 0;
}
