"""Public entrypoint for the bazel-single-header module.

Repository rule that downloads a single remote header file and generates an external
repository exposing it as a public cc_library (useful for STB-style single-header libs).
"""

load("//bazel/function:single_header.bzl", _single_header = "single_header")

single_header = _single_header
