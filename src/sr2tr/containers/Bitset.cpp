#include "Bitset.hpp"

namespace sr2tr::containers {

Bitset::Bitset(uint32_t length) : array(length, false) {}

Bitset::Bitset(const std::vector<bool> &new_array) { array = new_array; }

std::strong_ordering Bitset::operator<=>(const Bitset &to_compare) const {
    uint32_t nb_bits_in_bitset = count();
    uint32_t nb_bits_in_bitset_to_compare = to_compare.count();
    if (nb_bits_in_bitset == nb_bits_in_bitset_to_compare) {
        for (uint32_t index = 0; index < array.size(); index++) {
            if (array[index] != to_compare.array[index]) {
                return (array[index] <=> to_compare.array[index]);
            }
        }
    }
    return (nb_bits_in_bitset <=> to_compare);
}

void Bitset::print(std::ostream &stream) const {
    for (uint32_t index = 0; index < array.size(); index++) {
        if (array[index]) {
            stream << '1';
        } else {
            stream << '0';
        }
    }
}

}  // namespace sr2tr::containers