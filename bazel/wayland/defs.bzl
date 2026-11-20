"""Centralized Wayland protocol generation via a module extension."""

ProtocolsConfig = tag_class(attrs = {
    "url": attr.string(mandatory = True),
    "sha256": attr.string(mandatory = True),
    "strip_prefix": attr.string(mandatory = True),
    "mirror_urls": attr.string_list(),
    "vendored_archive": attr.label(allow_single_file = True),
})

# (archive-relative XML path, output basename used by RGFW includes)
_PROTOCOLS = [
    ("stable/xdg-shell/xdg-shell.xml", "xdg-shell"),
    ("unstable/xdg-decoration/xdg-decoration-unstable-v1.xml", "xdg-decoration-unstable-v1"),
    ("staging/xdg-toplevel-icon/xdg-toplevel-icon-v1.xml", "xdg-toplevel-icon-v1"),
    ("unstable/relative-pointer/relative-pointer-unstable-v1.xml", "relative-pointer-unstable-v1"),
    ("unstable/pointer-constraints/pointer-constraints-unstable-v1.xml", "pointer-constraints-unstable-v1"),
    ("unstable/xdg-output/xdg-output-unstable-v1.xml", "xdg-output-unstable-v1"),
]

def _generated_build(scanner):
    lines = [
        'load("@rules_cc//cc:defs.bzl", "cc_library")',
        "",
        "exports_files([",
    ]
    for xml, _name in _PROTOCOLS:
        lines.append('    "%s",' % xml)
    lines += ["])", ""]
    hdrs, srcs = [], []
    for xml, name in _PROTOCOLS:
        out_h = name + ".h"
        out_c = name + ".c"
        hdrs.append('        "%s",' % out_h)
        srcs.append('        "%s",' % out_c)
        rule = name.replace("-", "_")
        for tool_cmd, out in (("client-header", out_h), ("private-code", out_c)):
            lines += [
                "genrule(",
                '    name = "%s_%s",' % (rule, "hdr" if tool_cmd == "client-header" else "src"),
                '    srcs = ["%s"],' % xml,
                '    tools = ["%s"],' % scanner,
                '    outs = ["%s"],' % out,
                '    cmd = "$(location %s) %s $< $@",' % (scanner, tool_cmd),
                ")",
                "",
            ]
    lines += [
        "cc_library(",
        '    name = "wayland_protocols",',
        "    hdrs = [",
    ] + hdrs + [
        "    ],",
        "    srcs = [",
    ] + srcs + [
        "    ],",
        '    includes = ["."],',
        # private-code marks interface symbols hidden; link objects directly so
        # consumers (RGFW) can resolve them instead of an exporting .so.
        "    linkstatic = True,",
        '    visibility = ["//visibility:public"],',
        ")",
        "",
    ]
    return "\n".join(lines)

def _protocols_repo_impl(ctx):
    urls = [ctx.attr.url] + ctx.attr.mirror_urls
    if ctx.attr.vendored_archive:
        urls.append("file://" + str(ctx.path(ctx.attr.vendored_archive)))
    ctx.download_and_extract(
        url = urls,
        sha256 = ctx.attr.sha256,
        stripPrefix = ctx.attr.strip_prefix,
    )
    ctx.file("BUILD.bazel", _generated_build(ctx.attr.scanner))

_protocols_repo = repository_rule(
    implementation = _protocols_repo_impl,
    attrs = {
        "url": attr.string(mandatory = True),
        "sha256": attr.string(mandatory = True),
        "strip_prefix": attr.string(mandatory = True),
        "mirror_urls": attr.string_list(),
        "scanner": attr.string(mandatory = True),
        "vendored_archive": attr.label(allow_single_file = True),
    },
)

def _impl(mctx):
    seen = False
    for mod in mctx.modules:
        for tag in mod.tags.config:
            if seen:
                fail("exactly one protocols.config tag is supported")
            seen = True
            _protocols_repo(
                name = "wayland_protocols",
                url = tag.url,
                sha256 = tag.sha256,
                strip_prefix = tag.strip_prefix,
                mirror_urls = tag.mirror_urls,
                scanner = str(Label("@wayland//:wayland_scanner")),
                vendored_archive = tag.vendored_archive,
            )

protocols = module_extension(
    implementation = _impl,
    tag_classes = {"config": ProtocolsConfig},
)