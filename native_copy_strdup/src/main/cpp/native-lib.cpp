#include <jni.h>
#include <cstdlib>
#include <cstring>
#include <android/log.h>

extern "C"
JNIEXPORT void JNICALL
Java_org_example_nativecopystrdup_MainActivity_doleak(JNIEnv *env, jclass clazz, jstring imei) {
    const char* cimei = env->GetStringUTFChars(imei, nullptr);
    char* buffer = strdup(cimei);
    __android_log_print(ANDROID_LOG_INFO, "copy_strdup", "%s", buffer);
}
