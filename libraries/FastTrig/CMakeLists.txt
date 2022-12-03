idf_component_register(SRCS "FastTrig.cpp"
                    INCLUDE_DIRS .)

target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")
