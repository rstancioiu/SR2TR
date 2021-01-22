#include "core/Bitset.hpp"

#include "gtest/gtest.h"

TEST(Bitset, Constructor) {
    Bitset bitset;
    std::cout << bitset.count() << std::endl;
}
