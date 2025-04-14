#include "IPv4PrefixSet.h"
#include <iostream>

IPv4PrefixSet::IPv4PrefixSet() : head(nullptr){}

IPv4PrefixSet::~IPv4PrefixSet() {
    prefixNode* current = head;
    while (current != nullptr) {
        prefixNode* temp = current->next;
        delete current;
        current = temp;
    }
}

bool IPv4PrefixSet::add(uint32_t ip, uint8_t maskLength) {
    if (maskLength > 32) {
        return false;
    }

    prefixNode* current = head;
    while (current != nullptr) {
        if (current->ip == ip && current->maskLength == maskLength) {
            return false;
        }
        current = current->next;
    }

    prefixNode* newNode = new prefixNode{ip, maskLength, head};
    head = newNode;
    return true;
}

bool IPv4PrefixSet::del(uint32_t ip, uint8_t maskLength) {
    if (maskLength > 32) {
        return false;
    }

    prefixNode* current = head;
    prefixNode* previous = nullptr;
    while (current != nullptr) {
        if (current->ip == ip && current->maskLength == maskLength) {
            if (previous == nullptr) {
                head = current->next;
            }
            else {
                previous->next = current->next;
            }
            delete current;
            return true;
        }
        previous = current;
        current = current->next;
    }

    return false;
}

int IPv4PrefixSet::check(uint32_t ip) const {
    prefixNode* current = head;
    int maxMask = -1;

    while (current != nullptr) {
        uint32_t mask = (0xFFFFFFFF << (32 - current->maskLength));
        if ((ip & mask) == (current->ip & mask)) {
            if (current->maskLength > maxMask) {
                maxMask = current->maskLength;
            }
        }
        current = current->next;
    }
    return maxMask;
}