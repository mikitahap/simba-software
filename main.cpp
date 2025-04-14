#include <iostream>
#include "IPv4PrefixSet.h"

// Helper function to convert uint32_t IP to human-readable string
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
    if (prefixSet.add(ip2, 8)) {
        std::cout << "Added: " << ipToString(ip2) << "/8" << std::endl;
    }

    std::cout << "\nTrying to add a duplicate:" << std::endl;
    if (!prefixSet.add(ip1, 24)) {
        std::cout << "Already exists: " << ipToString(ip1) << "/24" << std::endl;
    }

    std::cout << "\nDeleting prefix 10.0.0.0/8:" << std::endl;
    if (prefixSet.del(ip2, 8)) {
        std::cout << "Deleted: " << ipToString(ip2) << "/8" << std::endl;
    }

    std::cout << "\nTrying to delete a non-existing prefix:" << std::endl;
    if (!prefixSet.del(ip2, 8)) {
        std::cout << "Not found: " << ipToString(ip2) << "/8" << std::endl;
    }

    return 0;
}
