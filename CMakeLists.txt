cmake_minimum_required(VERSION 3.2.2)

project(base.library)

include_directories("./")
include_directories("./common")
include_directories("./strings")
include_directories("./threading")

aux_source_directory(common COMMON_SRC)
aux_source_directory(strings STRINGS_SRC)
aux_source_directory(threading THREADING_SRC)

aux_source_directory(third_party/icu ICU_SRC)

LINK_LIBRARIES(pthread)

add_library(base ${COMMON_SRC} ${STRINGS_SRC} ${THREADING_SRC} ${ICU_SRC})

add_subdirectory(test)

