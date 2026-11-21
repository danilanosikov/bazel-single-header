# BCR draft (bazel-single-header)

This directory contains **draft** Bazel Central Registry entry files/instructions for `bazel-single-header`. They are **not** part of the module consumed by Bazel; submit the final versions to [bazelbuild/bazel-central-registry](https://github.com/bazelbuild/bazel-central-registry).

## Before submitting

1. Publish a public repo and a SemVer tag/release matching `MODULE.bazel` (e.g. `v0.1.0` for `0.1.0`).
2. After pushing tag `v0.1.0` to GitHub, compute the release source archive values for `source.json`:
   - `url`: `https://github.com/danilanosikov/bazel-single-header/archive/refs/tags/v0.1.0.tar.gz`
   - `strip_prefix`: `bazel-single-header-0.1.0` (GitHub tag archive layout)
   - `integrity`: Subresource Integrity hash (base64 `sha256-...`) of that exact archive. Example:
     - `curl -sL "https://github.com/danilanosikov/bazel-single-header/archive/refs/tags/v0.1.0.tar.gz" | openssl dgst -sha256 -binary | openssl base64 -A` (prefix result with `sha256-`)
3. Verify the archive contains `MODULE.bazel` at root after stripping and that presubmit targets build/test.
4. Replace remaining placeholders (`<REPLACE_WITH_BASE64_SRI_OF_v0.1.0_ARCHIVE>`, maintainer details as desired) in files under this folder, then copy into your BCR fork as:
   - `modules/bazel-single-header/metadata.json`
   - `modules/bazel-single-header/0.1.0/MODULE.bazel`
   - `modules/bazel-single-header/0.1.0/source.json`
   - `modules/bazel-single-header/0.1.0/presubmit.yml`
5. Run BCR presubmit checks per registry contribution guide and open a PR (or use `publish-to-bcr` automation).

## Notes

- `presubmit.yml` here assumes the smoke example can be exercised in BCR context; adjust tasks/modules to match BCR expectations for a rule-only module.
- Prefer immutable `commit` pins in any `git_override` documentation/examples.
