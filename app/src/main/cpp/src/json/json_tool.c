//
// Created by 86177 on 2024/9/13.
//
#include "json_tool.h"
#include "log/android_log.h"

//C调用C++实现的方法时，直接使用extern关键字声明要调用的C++方法，不能引起头文件不然会编译报错
//#include "utils/string_util.h"
extern int str_to_int(const char *str);

void parseJson(const char *json) {
    ALOGI("parseJson call name=%s", json);
    ALOGI("parseJson call int=%d", str_to_int(json));
}

