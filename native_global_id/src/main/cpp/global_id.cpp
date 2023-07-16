#include <jni.h>
#include <string>


static jclass context_cls;
static jmethodID system_service_mid;
static jfieldID tele_fid;
static jclass tm_cls;

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env;
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    context_cls = env->FindClass("android/content/Context");
    context_cls = (jclass) env->NewGlobalRef(context_cls);
    system_service_mid = env->GetMethodID(context_cls, "getSystemService",
                                          "(Ljava/lang/String;)Ljava/lang/Object;");
    tele_fid = env->GetStaticFieldID(context_cls, "TELEPHONY_SERVICE",
                                     "Ljava/lang/String;");
    tm_cls = env->FindClass("android/telephony/TelephonyManager");
    tm_cls = (jclass) env->NewGlobalRef(tm_cls);

    return JNI_VERSION_1_6;
}



extern "C"
JNIEXPORT jstring JNICALL
Java_org_example_nativeglobalid_MainActivity_getImei(JNIEnv *env, jclass clazz,
                                                     jobject context) {
    jstring str = (jstring) env->GetStaticObjectField(context_cls, tele_fid);
    jobject telephony = env->CallObjectMethod(context, system_service_mid, str);
    jmethodID mid;
    if (android_get_device_api_level() >= __ANDROID_API_O__ ) {
        mid = env->GetMethodID(tm_cls, "getImei", "()Ljava/lang/String;");
    } else {
        mid = env->GetMethodID(tm_cls, "getDeviceId", "()Ljava/lang/String;");
    }

    jstring imei = (jstring) env->CallObjectMethod(telephony, mid); // source
    return imei;
}
