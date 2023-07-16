#include <jni.h>
#include <cstdlib>
#include <cstring>
#include <android/log.h>

extern "C"
JNIEXPORT void JNICALL
Java_org_example_nativearrayregion_MainActivity_doLeak(JNIEnv *env, jclass clazz, jbyteArray buf) {
    jbyte buffer[30];
    jsize len = env->GetArrayLength(buf);
    env->GetByteArrayRegion(buf, 0, len, buffer);
    __android_log_print(ANDROID_LOG_INFO, "array_region", "%s", buffer);
}

