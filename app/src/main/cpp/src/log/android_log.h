//
// Created by 86177 on 2024/9/13.
//

#ifndef ANDROIDCPP_ANDROID_LOG_H
#define ANDROIDCPP_ANDROID_LOG_H

//'android/log.h' file not found
#include <android/log.h>

#define JNI_LOG_TAG "JNI_LOG_TAG"

#define ALOGI(...) __android_log_print(ANDROID_LOG_INFO,JNI_LOG_TAG,__VA_ARGS__)

#define ALOGE(...) __android_log_print(ANDROID_LOG_DEBUG,JNI_LOG_TAG,__VA_ARGS__)

#endif //ANDROIDCPP_ANDROID_LOG_H
