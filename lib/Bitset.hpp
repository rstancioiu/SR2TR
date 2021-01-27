#pragma once

#include <concepts>
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

class Bitset {
   public:
    Bitset(uint32_t length = 256u);

    Bitset(std::vector<bool> &new_bitset);

    void clear();

    bool empty() const;

    void set(uint32_t index, bool value);

    uint32_t count() const;

    bool check(uint32_t index) const;

    uint32_t size();

    void resize(uint32_t length);

    void print(std::ostream &stream) const;

    bool operator<(Bitset const &b) const;

    bool operator>(Bitset const &b) const;

    bool operator==(const Bitset &b) const;

    bool operator!=(const Bitset &b) const;

   private:
    std::vector<bool> bitset_array;
};

template <typename Object>
concept Printable = requires(std::ostream &stream, Object const &object) {
    {object.print(stream)};
};

template <Printable Object>
std::ostream &operator<<(std::ostream &stream, const Object &object) {
    object.print(stream);
    return stream;
}