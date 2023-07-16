#include <jni.h>
#include <cstdlib>
#include <cstring>
#include <android/log.h>

extern "C"
JNIEXPORT void JNICALL
Java_org_example_nativecopy_MainActivity_doleak(JNIEnv *env, jclass clazz, jstring imei) {
    const char* cimei = env->GetStringUTFChars(imei, nullptr);
    char* buffer = (char*) malloc(20);
    for (int i=0;i<19;i++) {
        buffer[i] = cimei[i];
    }
    buffer[19] = 0;
    __android_log_print(ANDROID_LOG_INFO, "copy", "%s", buffer);
}
