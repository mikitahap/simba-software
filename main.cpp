#include "IPv4PrefixSet.h"
#include <gtest/gtest.h>

TEST(IPv4PrefixSetTest, AddValidPrefixes) {
    IPv4PrefixSet set;

    EXPECT_TRUE(set.add(0xC0A80000, 16)); // 192.168.0.0/16
    EXPECT_TRUE(set.add(0xC0A80100, 24)); // 192.168.1.0/24
}

TEST(IPv4PrefixSetTest, AddExistingPrefix) {
    IPv4PrefixSet set;

    EXPECT_TRUE(set.add(0xC0A80000, 16));
    EXPECT_FALSE(set.add(0xC0A80000, 16));
}

TEST(IPv4PrefixSetTest, DeleteExistingAndNonExistingPrefixes) {
    IPv4PrefixSet set;
    set.add(0xC0A80000, 16);

    EXPECT_TRUE(set.del(0xC0A80000, 16));
    EXPECT_FALSE(set.del(0xC0A80000, 16));
    EXPECT_FALSE(set.del(0xC0A80100, 24));
}

TEST(IPv4PrefixSetTest, CheckMostSpecificMatch) {
    IPv4PrefixSet set;
    set.add(0xC0A80000, 16); // 192.168.0.0/16
    set.add(0xC0A80100, 24); // 192.168.1.0/24

    EXPECT_EQ(set.check(0xC0A8017B), 24);
}

TEST(IPv4PrefixSetTest, CheckNonExistingAdress) {
    IPv4PrefixSet set;
    set.add(0xC0A80000, 16); // 192.168.0.0/16

    EXPECT_EQ(set.check(0x0A000001), -1);
}

TEST(IPv4PrefixSetTest, EdgeCases_Mask0AndMask32) {
    IPv4PrefixSet set;
    set.add(0x00000000, 0); // 0.0.0.0/0
    set.add(0xC0A8017B, 32); // 192.168.1.123/32

    EXPECT_EQ(set.check(0xC0A8017B), 32);
    EXPECT_EQ(set.check(0x8F000001), 0); // 143.0.0.1
}
