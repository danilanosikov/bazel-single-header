# @описание: правило для загрузки одиночного заголовочного файла
# (http_file не умеет добавлять каталог заголовка в пути поиска компилятора,
# поэтому файл скачивается в корень репозитория и объявляется как cc_library)

def _single_header_impl(ctx):
    header = ctx.attr.header
    name = header.removesuffix(".h")
    ctx.download(ctx.attr.url, output = header, sha256 = ctx.attr.sha256)
    ctx.file("BUILD.bazel", """
load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "{name}",
    hdrs = ["{header}"],
    includes = ["."],
    visibility = ["//visibility:public"],
)
""".format(name = name, header = header))

single_header = repository_rule(
    implementation = _single_header_impl,
    attrs = {
        "url": attr.string(mandatory = True),
        "sha256": attr.string(mandatory = True),
        "header": attr.string(mandatory = True),
    },
)
