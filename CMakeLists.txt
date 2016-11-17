cmake_minimum_required(VERSION 3.2.2)

project(base.library)

include_directories("./")
include_directories("./common")
include_directories("./strings")

aux_source_directory(common COMMON_SRC)

add_library(base ${COMMON_SRC})

add_subdirectory(test)

