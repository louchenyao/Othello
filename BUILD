cc_library(
    name = "othello",
    hdrs = glob(["src/*.h"]),
    strip_include_prefix = "src",
    include_prefix = "othello",
    visibility = ["//visibility:public"]
)

COPTS = ["-std=c++17", "-O3", "-march=native",  "-Wall", "-Wextra", "-Werror"]

cc_test(
    name = "test",
    srcs = ["ssfe_benchmarks/othello_test.cpp"],
    copts = COPTS,
    deps = [
        ":othello",
        "@gtest//:gtest",
        "@gtest//:gtest_main",
    ]
)

cc_binary(
    name = "bench",
    srcs = ["ssfe_benchmarks/othello_bench.cpp"],
    copts = COPTS,
    defines = ["NO_OUTPUT", "DO_NOT_PRINT_SPACE"],
    deps = [
        ":othello",
        "@benchmark//:benchmark",
        "@benchmark//:benchmark_main",
    ]
)