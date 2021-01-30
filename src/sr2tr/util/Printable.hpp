#pragma once

#include <concepts>
#include <ostream>

namespace sr2tr {

template <typename Object>
concept Printable = requires(std::ostream &stream, Object const &object) {
    {object.print(stream)};
};

template <Printable Object>
std::ostream &operator<<(std::ostream &stream, const Object &object) {
    object.print(stream);
    return stream;
}

}  // namespace sr2tr