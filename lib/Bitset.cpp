#include "Bitset.hpp"

Bitset::Bitset(uint32_t length) : bitset_array(length, false) {}

Bitset::Bitset(std::vector<bool> &new_bitset) { bitset_array = new_bitset; }

void Bitset::clear() { std::fill(bitset_array.begin(), bitset_array.end(), 0); }

bool Bitset::empty() const {
    for (uint32_t index = 0; index < bitset_array.size(); index++) {
        if (bitset_array[index]) {
            return false;
        }
    }
    return true;
}

void Bitset::set(uint32_t index, bool bit) { bitset_array[index] = bit; }

uint32_t Bitset::count() const {
    uint32_t cnt = 0;
    for (uint32_t index = 0; index < bitset_array.size(); index++) {
        if (bitset_array[index]) {
            cnt++;
        }
    }
    return cnt;
}

bool Bitset::operator<(const Bitset &b) const {
    uint32_t s1 = count();
    uint32_t s2 = b.count();
    if (s1 != s2) {
        return (s1 < s2);
    }
    for (uint32_t index = 0; index < bitset_array.size(); index++) {
        if (bitset_array[index] != b.bitset_array[index]) {
            return bitset_array[index] < b.bitset_array[index];
        }
    }
    return false;
}

bool Bitset::operator>(const Bitset &b) const {
    uint32_t s1 = count();
    uint32_t s2 = b.count();
    if (s1 != s2) {
        return (s2 < s1);
    }
    for (uint32_t index = 0; index < bitset_array.size(); index++) {
        if (bitset_array[index] != b.bitset_array[index]) {
            return bitset_array[index] > b.bitset_array[index];
        }
    }
    return false;
}

void Bitset::resize(uint32_t length) { bitset_array.resize(length); }

void Bitset::print(std::ostream &stream) const {
    for (uint32_t index = 0; index < bitset_array.size(); index++) {
        if (bitset_array[index]) {
            stream << '1';
        } else {
            stream << '0';
        }
    }
}

bool Bitset::check(uint32_t index) const {
    if (index >= bitset_array.size()) {
        return false;
    }
    return bitset_array[index];
}

uint32_t Bitset::size() { return bitset_array.size(); }

bool Bitset::operator==(const Bitset &bs) const {
    return (bitset_array == bs.bitset_array);
}

bool Bitset::operator!=(const Bitset &bs) const {
    return (bitset_array != bs.bitset_array);
}
