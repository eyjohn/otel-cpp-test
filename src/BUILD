cc_library(
    name = "example_library",
    srcs = [
        "example.cpp",
    ],
    hdrs = [
        "example.h",
    ],
    deps = [
        "@opentelemetry_cpp//api",
    ],
)

cc_binary(
    name = "example_main",
    srcs = [
        "main.cpp",
    ],
    deps = [
        ":example_library",
        "@opentelemetry_cpp//api",
        "@opentelemetry_cpp//sdk/src/trace",
        "@opentelemetry_cpp//exporters/ostream:ostream_span_exporter",
    ],
)