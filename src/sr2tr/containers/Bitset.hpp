#pragma once

#include <cstdint>
#include <vector>

#include "../util/Printable.hpp"

namespace sr2tr::containers {

/*
 * Bitset is different from std::bitset because of:
 *  - a specific comparator function
 *  - length of the bitset changes at runtime
 */
class Bitset {
   public:
    Bitset(uint32_t length = 256u);

    Bitset(const std::vector<bool> &new_array);

    bool test(uint32_t index) const { return array.at(index); }

    void set(uint32_t index, bool bit) { array.at(index) = bit; }

    uint32_t size() { return array.size(); }

    void resize(uint32_t length) { array.resize(length); }

    std::strong_ordering operator<=>(const Bitset &to_compare) const;

    void print(std::ostream &stream) const;

   private:
    std::vector<bool> array;

    uint32_t count() const {
        return std::count(array.begin(), array.end(), true);
    }
};

}  // namespace sr2tr::containers