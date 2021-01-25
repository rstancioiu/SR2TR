load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_test")

cc_binary(
    name = "integration",
    srcs = ["tester.cpp"],
    deps = [
        "//lib:SR2TR",
    ],
)

cc_test(
    name = "integration_tests",
    srcs = [
        "Integration_tests.cpp"
    ],
    deps = [
        "//lib:SR2TR",
        "@googletest//:gtest_main",
    ],
    data = [
        "sample-tests/test1/source.csv",
        "sample-tests/test1/target.csv",
        "sample-tests/test2/source.csv",
        "sample-tests/test2/target.csv",
        "sample-tests/test3/source.csv",
        "sample-tests/test3/target.csv",
        "sample-tests/test4/source.csv",
        "sample-tests/test4/target.csv",
        "sample-tests/test5/source.csv",
        "sample-tests/test5/target.csv",
        "large-tests/source.csv",
        "large-tests/target.csv"
    ]
)
