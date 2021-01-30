#pragma once

#include <concepts>
#include <ostream>

template <typename Object>
concept Printable = requires(std::ostream &stream, Object const &object) {
    {object.print(stream)};
};

template <Printable Object>
std::ostream &operator<<(std::ostream &stream, const Object &object) {
    object.print(stream);
    return stream;
}