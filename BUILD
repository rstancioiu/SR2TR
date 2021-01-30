package(default_visibility = ["//visibility:public"])

load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
    name = "sr2tr",
    srcs = glob(
        include = [
            "src/*.cpp",
            "src/*.hpp",
            "src/**/*.cpp",
            "src/**/*.hpp",
        ],
        exclude = [
            "src/*_test.cpp",
            "src/**/*_test.cpp"
        ]
    ),
    hdrs = glob(["include/*.hpp",]),
    includes = ["include/"],
)

cc_binary(
    name = "command_line",
    srcs = ["command_line/main.cpp"],
    deps = [":sr2tr"],
    includes = ["include"],
)

cc_test(
    name = "unit_tests",
    size = "small",
    srcs = glob([
        "src/*_test.cpp",
        "src/**/*_test.cpp"
    ]),
    linkstatic = 0,
    deps = [
        ":sr2tr",
        "@googletest//:gtest_main"
    ],
)

cc_test(
    name = "integration_tests",
    size = "small",
    srcs = ["test/Integration_tests.cpp"],
    deps = [
        ":sr2tr",
        "@googletest//:gtest_main"
    ],
    data = glob([
        "test/large-tests/*.csv",
        "test/sample-tests/**/*.csv"
    ]),
)