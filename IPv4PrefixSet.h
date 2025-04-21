#include <cstdint>

#ifndef IPV4PREFIXSET_H
#define IPV4PREFIXSET_H

class IPv4PrefixSet {
private:
    struct prefixNode {
        uint32_t ip;
        uint8_t maskLength;
        prefixNode* next;
    };
    prefixNode* head;
public:
    IPv4PrefixSet();
    ~IPv4PrefixSet();

    uint32_t normalizePrefix(uint32_t ip, uint8_t maskLength);
    bool add(uint32_t base, uint8_t maskLength);
    bool del(uint32_t base, uint8_t maskLength);
    int check(uint32_t ip) const;
};

#endif