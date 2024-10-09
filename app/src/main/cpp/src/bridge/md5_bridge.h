//
// Created by 86177 on 2024/9/19.
//

#ifndef ANDROIDCPP_MD5_BRIDGE_H
#define ANDROIDCPP_MD5_BRIDGE_H
#ifdef __cplusplus
extern "C"
{
#endif

#include <jni.h>
#include "log/android_log.h"

jstring cmd5_calculate_md5(JNIEnv *env, jclass thiz, jstring str);

jstring cmd5_openssl_md5(JNIEnv *env, jclass thiz, jstring str);

static JNINativeMethod md5_native_method[] = {
        {"calculateMD5",  "(Ljava/lang/String;)Ljava/lang/String;", (void *) cmd5_calculate_md5},
        {"calOpensslMd5", "(Ljava/lang/String;)Ljava/lang/String;", (void *) cmd5_openssl_md5}
};

int register_md5_native_method(JNIEnv *pEnv);

#ifdef __cplusplus
}
#endif
#endif //ANDROIDCPP_MD5_BRIDGE_H
