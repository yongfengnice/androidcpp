//
// Created by 86177 on 2024/9/14.
//

#include "cjson_test.h"

void printf_cjson_version() {
    const char *version = cJSON_Version();
    ALOGI("cjson_version==%s", version);
}