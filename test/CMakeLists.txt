cmake_minimum_required(VERSION 3.2.2)

project(base.library.test)

include_directories(../)

LINK_DIRECTORIES(../)

LINK_LIBRARIES(base)
LINK_LIBRARIES(pthread)

aux_source_directory(. test_file)

FOREACH(src ${test_file})
    MESSAGE( ${src} )
    STRING( REPLACE "./" "" prj ${src})
    STRING( REPLACE ".cpp" "" prj ${prj})
    add_executable(${prj} ${src})
ENDFOREACH()
