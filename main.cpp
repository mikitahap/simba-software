#include "IPv4PrefixSet.h"
#include <gtest/gtest.h>

TEST(IPv4PrefixSetTest, AddValidPrefixes) {
    IPv4PrefixSet set;

    EXPECT_TRUE(set.add(0xA8D4E2CC, 16));
    EXPECT_TRUE(set.add(0xA000000, 24));
}

TEST(IPv4PrefixSetTest, AddExistingPrefix) {
    IPv4PrefixSet set;

    EXPECT_TRUE(set.add(0xA000000, 16));
    EXPECT_FALSE(set.add(0xA000000, 16));
}

TEST(IPv4PrefixSetTest, DeleteExistingAndNonExistingPrefixes) {
    IPv4PrefixSet set;
    set.add(0xA000000, 16);

    EXPECT_TRUE(set.del(0xA000000, 16));
    EXPECT_FALSE(set.del(0xA000000, 16));
    EXPECT_FALSE(set.del(0xC0A80100, 24));
}

TEST(IPv4PrefixSetTest, CheckMostSpecificMatch) {
    IPv4PrefixSet set;
    set.add(0xA000000, 16);
    set.add(0xA000000, 24);

    EXPECT_EQ(set.check(0xA000001), 24);
}

TEST(IPv4PrefixSetTest, CheckNonExistingAdress) {
    IPv4PrefixSet set;
    set.add(0xA000000, 16);

    EXPECT_EQ(set.check(0xA00001), -1);
}

TEST(IPv4PrefixSetTest, EdgeCases_Mask0AndMask32) {
    IPv4PrefixSet set;
    set.add(0x00000000, 0);
    set.add(0xA000000, 32);

    EXPECT_EQ(set.check(0xA000000), 32);
    EXPECT_EQ(set.check(0x00), 0);
}

TEST(IPv4PrefixSetTest, InvalidMaskLengths) {
    IPv4PrefixSet set;

    EXPECT_FALSE(set.add(0x01020304, 33));
    EXPECT_FALSE(set.add(0x01020304, 255));
}

TEST(IPv4PrefixSetTest, DeleteWithWrongMask) {
    IPv4PrefixSet set;

    set.add(0xA000000, 16);
    EXPECT_FALSE(set.del(0xA000000, 24));
}

TEST(IPv4PrefixSetTest, DeleteNormalizedPrefix) {
    IPv4PrefixSet set;
    set.add(0x0000000, 24);
    EXPECT_TRUE(set.del(0x0000001, 24));
}

TEST(IPv4PrefixSetTest, PrefixNormalization) {
    IPv4PrefixSet set;
    EXPECT_TRUE(set.add(0xC0A80101, 16));
    EXPECT_FALSE(set.add(0xC0A80202, 16));
    EXPECT_TRUE(set.add(0xC0A80000, 24));
    EXPECT_FALSE(set.add(0xC0A80080, 24));
}
