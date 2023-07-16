#include <jni.h>
#include <cstdlib>
#include <cstring>
#include <android/log.h>


extern "C"
JNIEXPORT void JNICALL
Java_org_example_nativedirectbuffer_MainActivity_doLeak(JNIEnv *env, jclass clazz, jobject buf) {
    char *buffer = (char*) env->GetDirectBufferAddress(buf);
    __android_log_print(ANDROID_LOG_INFO, "direct_buffer", "%s", buffer);
}
