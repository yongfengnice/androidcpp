//
// Created by 86177 on 2024/9/13.
//

#ifndef ANDROIDCPP_STRING_UTIL_HPP
#define ANDROIDCPP_STRING_UTIL_HPP

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
//#include "../../../../../../../../java/androidSdk/ndk/25.1.8937393/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include/c++/v1/string.h"

bool is_number(const char *str);

//C要调用的方法，声明要放在extern "C" { } 里面
int str_to_int(const char *str);

#ifdef __cplusplus
}
#endif

#endif //ANDROIDCPP_STRING_UTIL_HPP
