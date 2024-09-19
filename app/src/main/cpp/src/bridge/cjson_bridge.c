//
// Created by 86177 on 2024/9/19.
//

#include "cjson_bridge.h"

int cjson_parse_json(JNIEnv *env, jobject thiz, jstring json) {
    ALOGI("cjson_parse_json call");
}

static JNINativeMethod cjson_native_method[] = {
        {"parseJson", "(Ljava/lang/String;)I;", (void *) cjson_parse_json}
};

int register_cjson_native_method(JNIEnv *pEnv) {
    ALOGI("register_cjson_native_method call");
    jclass clazz = (*pEnv)->FindClass(pEnv, "com/suyf/androidcpp/jni/NativeCjsonBridge");
    if (clazz == NULL) {
        ALOGI("registerNativeMethod FindClass fail");
        return JNI_ERR;
    }
    const JNINativeMethod *methods = cjson_native_method;
    jint nMethods = sizeof(cjson_native_method) / sizeof(cjson_native_method[0]);
    return (*pEnv)->RegisterNatives(pEnv, clazz, methods, nMethods);
}
