#include "Bitset.hpp"

#include <sstream>

#include "gtest/gtest.h"

namespace sr2tr::containers {

TEST(Bitset, test) {
    Bitset bitset({false, true, false, true, false});
    ASSERT_FALSE(bitset.test(0));
    ASSERT_TRUE(bitset.test(1));
    ASSERT_FALSE(bitset.test(2));
    ASSERT_TRUE(bitset.test(3));
    ASSERT_FALSE(bitset.test(4));
    ASSERT_THROW(bitset.test(5), std::out_of_range);
}

TEST(Bitset, set) {
    Bitset bitset({false, true, false, true, false});
    bitset.set(0, true);
    ASSERT_TRUE(bitset.test(0));
}

TEST(Bitset, size) {
    Bitset bitset({false, true, false, true, false});
    ASSERT_EQ(5u, bitset.size());
}

TEST(Bitset, resize) {
    Bitset bitset({false, true, false, true, false});
    bitset.resize(1);
    ASSERT_EQ(1u, bitset.size());
}

TEST(Bitset, print) {
    std::ostringstream stream;
    Bitset bitset({false, true, false, true, false});
    bitset.print(stream);
    ASSERT_EQ("01010", stream.str());
}

TEST(Bitset, compare_operator) {
    Bitset bitset_1({false, true, false, true, false});
    Bitset bitset_2({true, false, true, false});
    ASSERT_TRUE(bitset_1 < bitset_2);
    ASSERT_TRUE(bitset_2 > bitset_1);
    ASSERT_TRUE(bitset_1 <= bitset_2);
    ASSERT_TRUE(bitset_2 >= bitset_1);
}

}  // namespace sr2tr::containers