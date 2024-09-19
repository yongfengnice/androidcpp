cmake_minimum_required(VERSION 3.0)

project(cJSON
        VERSION 1.7.18
        LANGUAGES C)

#cJSON
set(CJSON_LIB cjson)

file(GLOB HEADERS cJSON.h)
set(SOURCES cJSON.c)

add_library("${CJSON_LIB}" SHARED "${HEADERS}" "${SOURCES}")

#target_link_libraries("${CJSON_LIB}" m)

#add_subdirectory(tests)
