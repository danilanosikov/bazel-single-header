# bazel-single-header

Bazel module providing a `single_header` **repository rule** that downloads one remote header file (e.g. an STB-style single-header library) and generates an external repository exposing it as a public `cc_library`.

- Module name: `bazel-single-header`
- Rule: `single_header`
- Public load path (recommended): `@bazel-single-header//:single_header.bzl`
- Legacy load path: `@bazel-single-header//bazel/function:single_header.bzl`
- Requires: Bazel with bzlmod enabled (tested baseline via `.bazelversion`), `rules_cc`

- Canonical repository: `https://github.com/danilanosikov/bazel-single-header` (MIT `LICENSE` included). Create/push a SemVer git tag/release matching `MODULE.bazel`'s `version` (e.g. `v0.1.0`) before external fetch/BCR submission.

## API

```starlark
load("@bazel-single-header//:single_header.bzl", "single_header")

single_header(
    name = "stb_image",
    url = "https://raw.githubusercontent.com/nothings/stb/<commit>/stb_image.h",
    sha256 = "<sha256-of-header>",
    header = "stb_image.h",
)
```

Attributes:
- `name` (repo name): name of the generated external repository.
- `url` (string, required): URL to download the header from.
- `sha256` (string, required): SHA-256 of the downloaded file.
- `header` (string, required): header filename to materialize in the generated repo (target name is derived as `header.removesuffix(".h")`).

Generated repository layout/target:
- Downloads `<header>` into the external repo root.
- Generates a `BUILD.bazel` with a public `cc_library(name = "<header without .h>", hdrs = ["<header>"], includes = ["."])`.
- Consume as: `deps = ["@stb_image//:stb_image"]` and `#include "stb_image.h"`.

## Usage (Bzlmod, recommended)

In your root module's `MODULE.bazel`:

```starlark
bazel_dep(name = "bazel-single-header", version = "0.1.0")

# If the module is not resolved from a registry (e.g. BCR), add one of:
# git_override(
#     module_name = "bazel-single-header",
#     remote = "https://github.com/danilanosikov/bazel-single-header.git",
#     commit = "<immutable-commit-sha>",  # preferred (pin a released commit)
#     # tag = "v0.1.0",
# )
#
# archive_override(
#     module_name = "bazel-single-header",
#     urls = ["https://github.com/danilanosikov/bazel-single-header/archive/refs/tags/v0.1.0.tar.gz"],
#     integrity = "sha256-<base64-sri-of-release-archive>",
#     strip_prefix = "bazel-single-header-0.1.0",
# )

single_header = use_repo_rule("@bazel-single-header//:single_header.bzl", "single_header")

single_header(
    name = "stb_image",
    url = "https://raw.githubusercontent.com/nothings/stb/<commit>/stb_image.h",
    sha256 = "<sha256>",
    header = "stb_image.h",
)
```

Then in a `BUILD.bazel`:

```starlark
cc_binary(
    name = "app",
    srcs = ["main.c"],
    deps = ["@stb_image//:stb_image"],
)
```

Notes:
- `git_override` / `archive_override` take effect only in the **root** module.
- When fetching by release archive, `integrity` must be the correct Subresource Integrity value (e.g. `sha256-...`) and `strip_prefix` must match the archive's top-level directory (GitHub tag archives are typically `<repo>-<version>/`).

## Usage (legacy WORKSPACE)

Bzlmod is the primary supported workflow. For legacy WORKSPACE-based setups, fetch this repository (e.g. `http_archive`/`git_repository`) and then:

```starlark
load("@bazel-single-header//:single_header.bzl", "single_header")

single_header(
    name = "stb_image",
    url = "https://raw.githubusercontent.com/nothings/stb/<commit>/stb_image.h",
    sha256 = "<sha256>",
    header = "stb_image.h",
)
```

(Ensure `rules_cc` is available in the WORKSPACE graph as required by the generated repositories.)

## Publishing / making it fetchable

### As a standalone git module (no registry)
1. Ensure `MODULE.bazel` has the correct `name` and a SemVer `version` aligned with a git tag (e.g. `0.1.0` / `v0.1.0`).
2. Add a `LICENSE` and push to a public remote.
3. Create and push a tag/release; consumers can use `git_override` (pinned `commit`) or `archive_override` (release tarball + `integrity` + `strip_prefix`).

### To Bazel Central Registry (BCR)
BCR entries live in the registry repo (not this repo): `modules/bazel-single-header/` with `metadata.json` and per-version `source.json`, `MODULE.bazel`, and `presubmit.yml`.
1. Prepare this repo: stable SemVer tag/release, `LICENSE`, docs, and working build/test targets for presubmit.
2. Compute release archive URL, `strip_prefix`, and `sha256` integrity for `source.json`.
3. Submit/update the module entry in https://github.com/bazelbuild/bazel-central-registry (manually or via `publish-to-bcr`).

## Development notes

- `.bazelrc` enables bzlmod; `.bazelversion` pins a baseline Bazel version.
- `MODULE.bazel.lock` may need regeneration after dependency/version changes (`bazel mod deps` / relevant Bazel commands).
- Current repo state may include internal history/remote; set the intended public `origin` before publishing.
