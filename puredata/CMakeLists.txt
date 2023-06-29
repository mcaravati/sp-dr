cmake_minimum_required(VERSION 3.15)
project(ergo_jr_pd_external)

# Add sources
add_executable(ergo_jr_pd_external
    src/main.c
    src/tinyosc/tinyosc.c
)