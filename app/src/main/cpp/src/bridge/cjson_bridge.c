//
// Created by 86177 on 2024/9/19.
//

#include "cjson_bridge.h"

int cjson_parse_json(JNIEnv *env, jclass thiz, jstring json) {
    const char *c_json = (*env)->GetStringUTFChars(env, json, JNI_FALSE);
    ALOGI("cjson_parse_json call==%s", c_json);
    cJSON *root = cJSON_Parse(c_json);
    if (root == NULL) {
        ALOGE("cjson_parse_json error=%s", cJSON_GetErrorPtr());
        return -1;
    }

    char *name = cJSON_GetStringValue(cJSON_GetObjectItem(root, "name"));
    ALOGI("cjson_parse_json name==%s", name);
    char *address = cJSON_GetStringValue(cJSON_GetObjectItem(root, "address"));
    ALOGI("cjson_parse_json address==%s", address);

    cJSON *ageJson = cJSON_GetObjectItem(root, "age");
    if(cJSON_IsNumber(ageJson)){
        ALOGI("cjson_parse_json age==%d", ageJson->valueint);
    }
    cJSON_Delete(root);
}

int register_cjson_native_method(JNIEnv *pEnv) {
    ALOGI("register_cjson_native_method call");
    jclass clazz = (*pEnv)->FindClass(pEnv, "com/suyf/androidcpp/jni/NativeCjsonBridge");
    if (clazz == NULL) {
        ALOGI("register_cjson_native_method FindClass fail");
        return JNI_ERR;
    }
    const JNINativeMethod *methods = cjson_native_method;
    jint nMethods = sizeof(cjson_native_method) / sizeof(cjson_native_method[0]);
    return (*pEnv)->RegisterNatives(pEnv, clazz, methods, nMethods);
}
