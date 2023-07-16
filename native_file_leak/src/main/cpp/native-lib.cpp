#include <jni.h>
#include <cstdlib>
#include <cstring>
#include <android/log.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

extern "C"
JNIEXPORT void JNICALL
Java_org_example_nativefileleak_MainActivity_doleak(JNIEnv *env, jclass clazz, jstring imei) {
    const char* cimei = env->GetStringUTFChars(imei, nullptr);
    int fd = open("/mnt/sdcard/info.txt", O_CREAT | O_WRONLY, 0642);
    if (fd == -1) {
        __android_log_print(ANDROID_LOG_INFO, "fileleak","file read failed: %s\n", strerror(errno));
    }
    else {
        write(fd, cimei, 30);
        close(fd);
    }
}
