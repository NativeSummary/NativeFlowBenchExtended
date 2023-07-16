#include <jni.h>
#include <cstdlib>
#include <cstring>
#include <android/log.h>

extern "C"
JNIEXPORT void JNICALL
Java_org_example_nativearrayelements_MainActivity_doLeak(JNIEnv *env, jclass clazz, jbyteArray buf) {
    jsize len = env->GetArrayLength(buf);
    jbyte *buffer = env->GetByteArrayElements(buf, nullptr);
    __android_log_print(ANDROID_LOG_INFO, "array_elements", "%s", buffer);
    env->ReleaseByteArrayElements(buf, buffer, 0);
}

