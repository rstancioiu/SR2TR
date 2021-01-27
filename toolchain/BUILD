# Copyright 2016 The Bazel Authors. All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# This becomes the BUILD file for @local_config_cc// under non-BSD unixes.

package(default_visibility = ["//visibility:public"])

load("@rules_cc//cc:defs.bzl", "cc_toolchain", "cc_toolchain_suite")
load("@local_config_cc//:cc_toolchain_config.bzl", "cc_toolchain_config")


filegroup(
    name = "empty",
    srcs = []
)

cc_toolchain_suite(
    name = "gcc10_toolchain_suite",
    toolchains = {
        "k8": ":gcc10_toolchain",
    },
)

cc_toolchain(
    name = "gcc10_toolchain",
    toolchain_identifier = "gcc10-toolchain",
    toolchain_config = ":gcc10_toolchain_config",
    all_files = ":empty",
    compiler_files = ":empty",
    dwp_files = ":empty",
    linker_files = ":empty",
    objcopy_files = ":empty",
    strip_files = ":empty",
    supports_param_files = 0,
)

cc_toolchain_config(
    name = "gcc10_toolchain_config",
    cpu = "k8",
    compiler = "compiler",
    toolchain_identifier = "local",
    host_system_name = "local",
    target_system_name = "local",
    target_libc = "local",
    abi_version = "local",
    abi_libc_version = "local",
    cxx_builtin_include_directories = ["/usr/lib/gcc/x86_64-linux-gnu/10/include",
    "/usr/local/include",
    "/usr/include/x86_64-linux-gnu",
    "/usr/include",
    "/usr/include/c++/10",
    "/usr/include/x86_64-linux-gnu/c++/10",
    "/usr/include/c++/10/backward"],
    tool_paths = {
        "ar": "/usr/bin/ar",
        "ld": "/usr/bin/ld",
        "llvm-cov": "/usr/bin/llvm-cov-10",
        "cpp": "/usr/bin/cpp-10",
        "gcc": "/usr/bin/gcc-10",
        "dwp": "/usr/bin/dwp",
        "gcov": "/usr/bin/gcov-10",
        "nm": "/usr/bin/nm",
        "objcopy": "/usr/bin/objcopy",
        "objdump": "/usr/bin/objdump",
        "strip": "/usr/bin/strip"
    },
    compile_flags = ["-U_FORTIFY_SOURCE",
    "-fstack-protector",
    "-Wall",
    "-Wunused-but-set-parameter",
    "-Wno-free-nonheap-object",
    "-fno-omit-frame-pointer"],
    opt_compile_flags = ["-g0",
    "-O2",
    "-D_FORTIFY_SOURCE=1",
    "-DNDEBUG",
    "-ffunction-sections",
    "-fdata-sections"],
    dbg_compile_flags = ["-g"],
    cxx_flags = ["-std=c++20"],
    link_flags = ["-fuse-ld=gold",
    "-Wl,-no-as-needed",
    "-Wl,-z,relro,-z,now",
    "-B/usr/bin",
    "-pass-exit-codes",
    "-lstdc++",
    "-lm"],
    link_libs = [],
    opt_link_flags = ["-Wl,--gc-sections"],
    unfiltered_compile_flags = ["-fno-canonical-system-headers",
    "-Wno-builtin-macro-redefined",
    "-D__DATE__=\"redacted\"",
    "-D__TIMESTAMP__=\"redacted\"",
    "-D__TIME__=\"redacted\""],
    coverage_compile_flags = ["--coverage"],
    coverage_link_flags = ["--coverage"],
    supports_start_end_lib = True,
)
