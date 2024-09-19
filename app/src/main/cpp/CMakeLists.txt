cmake_minimum_required(VERSION 3.22.1)

project("androidcpp" CXX C ASM)

#PROJECT_SOURCE_DIR==D:/work/androidcpp/app/src/main/cpp
message("PROJECT_SOURCE_DIR==${PROJECT_SOURCE_DIR}")

set(src_dir "src")
set(sub_dir "submodule")


#包含头文件，这样用于头文件的地方就只需要从“include之后开始”
#比如头文件：D:\work\androidcpp\app\src\main\cpp\include\log\android_log.h
#引入android_log.h头文件的时候只需要写 #include "log/android_log.h"
#include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${src_dir}")
include_directories("${PROJECT_SOURCE_DIR}/${sub_dir}")
#include_directories("${header_dir}/json")
#include_directories("${header_dir}/log")
#include_directories("${header_dir}/utils")

aux_source_directory("${src_dir}" root_src)
aux_source_directory("${src_dir}/file" file_src)
aux_source_directory("${src_dir}/json" json_src)
aux_source_directory("${src_dir}/network" network_src)
aux_source_directory("${src_dir}/sign" sign_src)
aux_source_directory("${src_dir}/utils" utils_src)

message("root_src=${root_src}")
message("hello,123")

add_subdirectory("${sub_dir}/cJSON")

add_library(${CMAKE_PROJECT_NAME} SHARED
        ${root_src}
        ${file_src}
        ${json_src}
        ${network_src}
        ${sign_src}
        ${utils_src})

target_link_libraries(${CMAKE_PROJECT_NAME}
        android
        cjson
        log)