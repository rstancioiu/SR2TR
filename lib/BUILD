load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "bitset",
    srcs = [
        "Bitset.cpp"
    ],
    hdrs = [
        "Bitset.hpp",
        "Util.hpp"
    ],
)

cc_test(
    name = "bitset_test",
    srcs = [
        "Bitset_test.cpp"
    ],
    deps = [
        ":bitset",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "SR2TR",
    srcs = [
        "CR.cpp",
        "Hungarian.cpp",
        "Mapping.cpp",
        "Reader.cpp",
        "ReadTextFile.cpp",
        "UIND.cpp"
    ],
    hdrs = [
        "Bitset.hpp",
        "CR.hpp",
        "Hungarian.hpp",
        "Mapping.hpp",
        "Reader.hpp",
        "ReadTextFile.hpp",
        "Relation.hpp",
        "UIND.hpp",
        "Util.hpp"
    ],
    deps = [
        ":bitset"
    ],
    visibility = [
        "//command-line:__pkg__",
        "//test:__pkg__"
    ],
)
