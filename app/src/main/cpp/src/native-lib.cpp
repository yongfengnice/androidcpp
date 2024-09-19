#include <jni.h>
#include <string>
#include <assert.h>
#include "log/android_log.h"

//C++调用C实现的方法时候，引入C头文件需要放在 extern "C" {} 里面
extern "C" {
#include "json/json_tool.h"
#include "json/cjson_test.h"
#include "utils/md5_tool.h"
#include "bridge/cjson_bridge.h"
#include "bridge/md5_bridge.h"
}

extern "C" JNIEXPORT jstring
JNICALL
Java_com_suyf_androidcpp_MainActivity_stringFromJNI(JNIEnv *env, jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    ALOGE("JNI_OnLoad.........");
    JNIEnv *env = nullptr;
    int ret = vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6);
    if (ret != JNI_OK) {
        ALOGE("JNI_OnLoad-GetEnv-fail");
        return -1;
    }
    ALOGI("JNI_OnLoad-GetEnv-OK=%d,", env != nullptr);
    assert(env != nullptr);

    ret = register_cjson_native_method(env);
    ALOGI("JNI_OnLoad-register_cjson_native_method-result=%d,", ret);

    ret = register_md5_native_method(env);
    ALOGI("JNI_OnLoad-register_md5_native_method-result=%d,", ret);

    return JNI_VERSION_1_6;
}
