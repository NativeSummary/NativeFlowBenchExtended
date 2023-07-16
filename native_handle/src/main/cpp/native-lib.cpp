#include <jni.h>
#include <cstdlib>
#include <cstring>
#include <android/log.h>


extern "C"
JNIEXPORT jlong JNICALL
Java_org_example_nativehandle_MainActivity_allocateInNative(JNIEnv *env, jclass clazz, jlong siza) {
//
//    return (jlong) strdup(ptr);
    return (jlong) malloc(siza);
}

extern "C"
JNIEXPORT void JNICALL
Java_org_example_nativehandle_MainActivity_setStringInNative(JNIEnv *env, jclass clazz,
                                                             jlong handle, jstring str, jlong size) {
    const char* ptr = env->GetStringUTFChars(str, nullptr);
    char* buffer = (char*) handle;
    strncpy(buffer, ptr, size);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_org_example_nativehandle_MainActivity_readStringFromNative(JNIEnv *env, jclass clazz,
                                                            jlong handle) {
    return env->NewStringUTF((char*)handle);
}

extern "C"
JNIEXPORT void JNICALL
Java_org_example_nativehandle_MainActivity_leakInNative(JNIEnv *env, jclass clazz,
                                                                jlong handle) {
    __android_log_print(ANDROID_LOG_INFO, "handle", "%s", (char*)handle);
}

extern "C"
JNIEXPORT void JNICALL
Java_org_example_nativehandle_MainActivity_releaseInNative(JNIEnv *env, jclass clazz, jlong handle) {
    free((void*)handle);
}
