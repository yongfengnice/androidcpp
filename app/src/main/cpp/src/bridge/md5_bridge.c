//
// Created by 86177 on 2024/9/19.
//

#include "md5_bridge.h"

jstring cmd5_calculate_md5(JNIEnv *env, jclass thiz, jstring str) {
    const char *c_str = (*env)->GetStringUTFChars(env, str, JNI_FALSE);
    char *ret = main_md5_tool2(c_str);
    ALOGI("cmd5_calculate_md5 str=%s ret=%s", c_str, ret);
    return (*env)->NewStringUTF(env, ret);
}

int register_md5_native_method(JNIEnv *pEnv) {
    ALOGI("register_md5_native_method call");
    jclass clazz = (*pEnv)->FindClass(pEnv, "com/suyf/androidcpp/jni/NativeMD5Bridge");
    if (clazz == NULL) {
        ALOGI("register_md5_native_method FindClass fail");
        return JNI_ERR;
    }
    const JNINativeMethod *methods = md5_native_method;
    jint nMethods = sizeof(md5_native_method) / sizeof(md5_native_method[0]);
    return (*pEnv)->RegisterNatives(pEnv, clazz, methods, nMethods);
}
