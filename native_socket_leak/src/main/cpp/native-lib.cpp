#include <jni.h>
#include <cstdlib>
#include <cstring>
#include <android/log.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


extern "C"
JNIEXPORT void JNICALL
Java_org_example_nativesocketleak_MainActivity_doleak(JNIEnv *env, jclass clazz, jstring imei) {
    const char* cimei = env->GetStringUTFChars(imei, nullptr);
    int sockFD, new_socket;
    char * message;
    if ((sockFD = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        __android_log_print(ANDROID_LOG_INFO, "socket_leak","Unable to create socket: %s\n", strerror(errno));
        return;
    }
    struct sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(3000);
    if (connect(sockFD, (struct sockaddr *)&server, sizeof(server)) < 0) {
        __android_log_print(ANDROID_LOG_INFO, "socket_leak","Connect Failed: %s\n", strerror(errno));
        return;
    }
    if (write(sockFD, cimei, strlen(cimei)) <= 0) {
        __android_log_print(ANDROID_LOG_INFO, "socket_leak","Write Failed: %s\n", strerror(errno));
        return;
    }
    __android_log_print(ANDROID_LOG_INFO, "socket_leak","OK.\n");
}
