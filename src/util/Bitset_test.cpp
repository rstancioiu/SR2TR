#include "Bitset.hpp"

#include "gtest/gtest.h"

TEST(Bitset, count) {
    Bitset bitset;
    ASSERT_EQ(0u, bitset.count());
    bitset.set(1, true);
    ASSERT_EQ(1u, bitset.count());
}
