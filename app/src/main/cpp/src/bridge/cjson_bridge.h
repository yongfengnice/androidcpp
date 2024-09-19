//
// Created by 86177 on 2024/9/19.
//

#ifndef ANDROIDCPP_CJSON_BRIDGE_H
#define ANDROIDCPP_CJSON_BRIDGE_H
#ifdef __cplusplus
extern "C"
{
#endif

#include <jni.h>
#include "log/android_log.h"

int register_cjson_native_method(JNIEnv *pEnv);

#ifdef __cplusplus
}
#endif
#endif //ANDROIDCPP_CJSON_BRIDGE_H
