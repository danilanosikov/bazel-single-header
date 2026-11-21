# bazel функции

- `single_header.bzl`: repository rule for fetching a single remote header and exposing it as a `cc_library` (designed for STB-style single-header libraries).
- Recommended public load path for consumers: `@bazel-single-header//:single_header.bzl` (root wrapper). Legacy path still works: `@bazel-single-header//bazel/function:single_header.bzl`.

