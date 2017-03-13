targets {
    "blessings_static" : {
        "target_type" : "lib_static",
        "sources_dict" : "blessings",
        "target_name" : "blessings_static",
        "output_name" : "blessings",
        "compiler_types" : [
            "gcc",
            "clang",
            "mingw"
        ],
        "compiler_flags" : {
            "gcc" : "-O3",
            "clang" : "-O3",
            "mingw" : "-O3"
        }
    }
}
