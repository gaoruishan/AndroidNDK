//
// Created by gaoruishan on 16/9/27.
//
#include <stdio.h>
#include <stdlib.h>
#include "com_gaoruishan_androidndk_JNI.h"
#include <android/log.h>

#define LOG_TAG "com.gaoruishan"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOG(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#define CLASS_CHAR "com/gaoruishan/androidndk/JNI"

/**
 * 返回值 char* 这个代表char数组的首地址
 *  Jstring2CStr 把java中的jstring的类型转化成一个c语言中的char 字符串
 */
char *Jstring2CStr(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
    jclass clsstring = (*env)->FindClass(env, "java/lang/String");
    jstring strencode = (*env)->NewStringUTF(env, "GB2312");
    jmethodID mid = (*env)->GetMethodID(env, clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) (*env)->CallObjectMethod(env, jstr, mid,
                                                            strencode); // String .getByte("GB2312");
    jsize alen = (*env)->GetArrayLength(env, barr);
    jbyte *ba = (*env)->GetByteArrayElements(env, barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char *) malloc(alen + 1);         //"\0"
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    (*env)->ReleaseByteArrayElements(env, barr, ba, 0);  //
    return rtn;
}
/**
 * JNIEnv 类型代表了java环境 通过JNIEnv* 指针,就可以对java端的代码进行操作
 * 创建java类的对象,调用java对象的方法,获取java对象的属性 等等.
 * jobject obj 就是当前方法所在的类代表的对象,代表的是JNI
 */
JNIEXPORT jstring JNICALL Java_com_gaoruishan_androidndk_JNI_getString__
        (JNIEnv *env, jobject jobject1) {
    LOG("get void string");
    // NewStringUTF 将常量字符转 jstring
    return (*env)->NewStringUTF(env, "你好，jni");
}

JNIEXPORT jstring JNICALL Java_com_gaoruishan_androidndk_JNI_getString__Ljava_lang_String_2
        (JNIEnv *env, jobject jobject1, jstring jstring1) {
    //在c语言中 是没有java的String
    char *string = Jstring2CStr(env, jstring1);
    //使用数组表示字符串 c语言中的字符串 都是以'/0' 作为结尾
    char addStr[8] = {' ', 'f', 'r', 'o', 'm', ' ', 'c', '\0'};
    strcat(string, addStr);//将addStr 添加到string后面
    return (*env)->NewStringUTF(env, string);
}

JNIEXPORT jint JNICALL Java_com_gaoruishan_androidndk_JNI_getInt
        (JNIEnv *env, jobject jobject1, jint i, jint j) {
    //java 和 C 中int 都是4个字节
    LOG("i=%d,j=$d", i, j);
    return i + j;
}

JNIEXPORT jintArray JNICALL Java_com_gaoruishan_androidndk_JNI_getIntArray
        (JNIEnv *env, jobject jobject1, jintArray array) {
    //1.知道数组的长度
    jsize len = (*env)->GetArrayLength(env, array);
    LOG("len=%d\n", len);
    //2.操作这个数组里面的每一个元素 GetIntArrayElements
    jint *arr = (*env)->GetIntArrayElements(env, array, NULL);//1 表示true
    int i = 0;//c99
    for (; i < len; i++) {
        LOG("arr=%d\n", arr[i]);
//        arr[i] += 10;
        *(arr + i) += 10;
        LOG("newArr=%d\n", arr[i]);
    }
    // c语言释放掉 刚才申请的内存空间
    (*env)->ReleaseIntArrayElements(env, array, arr, 0);
    return array;
}
/**
 * C代码调用Java代码的方法--类似Java中反射
 */
JNIEXPORT void JNICALL Java_com_gaoruishan_androidndk_JNI_callGet
        (JNIEnv *env, jobject jobject1) {
    //1,找到Java代码中的class文件 -> FindClass
    jclass jclass1 = (*env)->FindClass(env, CLASS_CHAR);
    if (jclass1 == 0) {//判断
        LOG("find class error");
        return;
    }
    //2,寻找class里面的方法
    jmethodID jmethodID1 = (*env)->GetMethodID(env, jclass1, "getFromJava", "()V");
    if (jmethodID1 == 0) {
        LOG("find method error");
        return;
    }
    //3.调用这个方法 CallVoidMethod 没有返回值方法
    (*env)->CallVoidMethod(env, jobject1, jmethodID1);
}

JNIEXPORT void JNICALL Java_com_gaoruishan_androidndk_JNI_callSetString
        (JNIEnv *env, jobject jobject1) {
    jclass jclass1 = (*env)->FindClass(env, CLASS_CHAR);
    jmethodID jmethodID1 = (*env)->GetMethodID(env, jclass1, "setStringFromJava",
                                               "(Ljava/lang/String;)V");
    (*env)->CallVoidMethod(env, jobject1, jmethodID1,(*env)->NewStringUTF(env,"this is from C"));
}

JNIEXPORT void JNICALL Java_com_gaoruishan_androidndk_JNI_callGetInt
        (JNIEnv *env, jobject jobject1) {
    jclass  jclass1 = (*env)->FindClass(env,CLASS_CHAR);
    jmethodID  jmethodID1 = (*env)->GetMethodID(env,jclass1,"getIntFromJava","(II)I");
    (*env)->CallIntMethod(env,jobject1,jmethodID1,2,4);
}