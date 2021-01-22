load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "Bitset",
    srcs = [
        "Bitset.cpp"
    ],
    hdrs = [
        "Bitset.hpp",
        "Util.hpp"
    ],
)

cc_test(
    name = "Bitset_test",
    srcs = [
        "Bitset_test.cpp"
    ],
    deps = [
        ":Bitset",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "SR2TR",
    srcs = [
        "Bitset.cpp",
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
        "UIND.hpp",
        "Util.hpp"
    ],
    visibility = ["//command-line:__pkg__"],
)
