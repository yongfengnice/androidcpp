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
}

void call_parseJson(const char *name) {
    parseJson(name);
    parseJson("1000");
}

jstring native_method_name(JNIEnv *env, jobject thiz, jstring name) {
    std::string jni_name = "jni_name:";
    const char *java_name = env->GetStringUTFChars(name, JNI_FALSE);
    ALOGI("native_method_name=%s", java_name);
    jni_name.append(java_name);
    call_parseJson(jni_name.c_str());
    return env->NewStringUTF(jni_name.c_str());
}

JNICALL
extern "C"
JNIEXPORT void JNICALL
Java_com_suyf_androidcpp_jni_NativeMethodBridge_callMd5(JNIEnv *env, jclass clazz) {
    char md5_str[33];
    ALOGI("md5_str=len=%d", (int) sizeof(md5_str));
    main_md5_tool(md5_str, sizeof(md5_str), "hello,world123");
    ALOGI("md5-str==%s", md5_str);

    //打印cjson版本号
    printf_cjson_version();
}


static JNINativeMethod jniNativeMethod[] = {
        {"javaMethodName", "(Ljava/lang/String;)Ljava/lang/String;", (void *) native_method_name}
};

int registerCJsonNativeMethod();

extern "C" JNIEXPORT jstring

JNICALL
Java_com_suyf_androidcpp_MainActivity_stringFromJNI(JNIEnv *env, jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

jint registerNativeMethod(JNIEnv *pEnv) {
    ALOGI("registerNativeMethod call");
    jclass clazz = pEnv->FindClass("com/suyf/androidcpp/jni/JavaMethodBridge");
    if (clazz == nullptr) {
        ALOGI("registerNativeMethod FindClass fail");
        return JNI_ERR;
    }
    const JNINativeMethod *methods = jniNativeMethod;
    jint nMethods = sizeof(jniNativeMethod) / sizeof(jniNativeMethod[0]);
    return pEnv->RegisterNatives(clazz, methods, nMethods);
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
    ret = registerNativeMethod(env);
    ALOGI("JNI_OnLoad-registerNativeMethod-result=%d,", ret);

    ret = register_cjson_native_method(env);
    ALOGI("JNI_OnLoad-registerCJsonNativeMethod-result=%d,", ret);
    return JNI_VERSION_1_6;
}
