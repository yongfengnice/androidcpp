//
// Created by 86177 on 2024/11/26.
//

#include "openssl/rsa.h"
#include "openssl/pem.h"
#include "openssl/err.h"
#include "openssl/evp.h"
#include "openssl/ec.h"
#include <string>
#include <unistd.h>
#include "openssl_sm2.hpp"
#include "log/android_log.h"

std::string GetErrorStr() {
    unsigned long er = 0;
    char erbuf[512] = {0};
    size_t erlen = 512;
    er = ERR_get_error();
    ERR_error_string_n(er, erbuf, erlen);
    return std::string(erbuf, erlen);
}

int my_sm2encrpt(std::string keystr, unsigned char *sourStr, int cStrlen, unsigned char *enStr) {
    BIO *bp = NULL;
    EVP_PKEY *pkey = NULL;
    EVP_PKEY_CTX *ectx = NULL;
    size_t cEnStrlen;
    char *cEnStr = NULL;
    char *chPublicKey = const_cast<char *>(keystr.c_str());
    int ret = -1;
    if ((bp = BIO_new_mem_buf(chPublicKey, -1)) == NULL) {
        ALOGE("BIO_new_mem_buf failed!\n");
        return 0;
    }
    pkey = PEM_read_bio_PUBKEY(bp, NULL, NULL, NULL);
    BIO_free_all(bp);
//     要去掉，不然执行EVP_PKEY_encrypt_init会报错返回-2
//    if ((EVP_PKEY_set_type(pkey, EVP_PKEY_SM2)) != 1) {
//        goto clean_up;
//    }

    if (!(ectx = EVP_PKEY_CTX_new(pkey, NULL))) {
        goto clean_up;
    }

    ret = EVP_PKEY_encrypt_init(ectx);
    ALOGI("EVP_PKEY_encrypt_init ret=%d\n", ret);
    if (ret != 1) {
        ALOGI("EVP_PKEY_encrypt_init error=%s\n", GetErrorStr().c_str());
        goto clean_up;
    }

    if ((EVP_PKEY_encrypt(ectx, NULL, &cEnStrlen, reinterpret_cast<unsigned char *>(sourStr),
                          (size_t) (cStrlen))) != 1) {
        goto clean_up;
    }
    if (!(cEnStr = (char *) malloc(cEnStrlen))) {
        goto clean_up;
    }

    if ((EVP_PKEY_encrypt(ectx, reinterpret_cast<unsigned char *>(cEnStr), &cEnStrlen,
                          reinterpret_cast<unsigned char *>(sourStr), cStrlen)) != 1) {
        goto clean_up;
    }
    ALOGI("enStrLen2: %ld\n", cEnStrlen);
    memcpy(enStr, cEnStr, cEnStrlen);
    return (int) (cEnStrlen);

    clean_up:

    if (pkey) {
        EVP_PKEY_free(pkey);
    }
    if (ectx) {
        EVP_PKEY_CTX_free(ectx);
    }
    if (cEnStr) {
        free(cEnStr);
    }
    return 0;
}

int dencryptStr(std::string keystr, unsigned char *cEnStr, int cEnstrlen, unsigned char *deStr) {
    BIO *priBp = NULL;
    EVP_PKEY *mSm2PriKey;
    EVP_PKEY_CTX *ectx = NULL;
    size_t cDeStrlen = 0;
    char *cDeStr = NULL;
    //create pri key
    char *chPrilicKey = const_cast<char *>(keystr.c_str());
    if ((priBp = BIO_new_mem_buf(chPrilicKey, -1)) == NULL) {
        ALOGE("BIO_new_mem_buf failed!\n");
    }
    mSm2PriKey = PEM_read_bio_PrivateKey(priBp, NULL, NULL, NULL);
    BIO_free_all(priBp);
    if (NULL == mSm2PriKey) {
        ERR_load_crypto_strings();
        char errBuf[512];
        ERR_error_string_n(ERR_get_error(), errBuf, sizeof(errBuf));
        ALOGE("load sm2 private key failed[%s]\n", errBuf);
    }
    //解密
//     要去掉，不然执行EVP_PKEY_encrypt_init会报错返回-2
//    if ((EVP_PKEY_set_type(mSm2PriKey, EVP_PKEY_SM2)) != 1) {
//        ALOGE("EVP_PKEY_set_alias_type failed!\n");
//    }

    if (!(ectx = EVP_PKEY_CTX_new(mSm2PriKey, NULL))) {
        ALOGE("EVP_PKEY_CTX_new failed!\n");
    }
    if ((EVP_PKEY_decrypt_init(ectx)) != 1) {
        ALOGE("EVP_PKEY_decrypt_init failed!\n");
    }
    if ((EVP_PKEY_decrypt(ectx, NULL, &cDeStrlen, reinterpret_cast<unsigned char *>(cEnStr),
                          cEnstrlen)) != 1) {
        ALOGE("EVP_PKEY_decrypt failed!\n");
        ERR_load_crypto_strings();
        char errBuf[512];
        ERR_error_string_n(ERR_get_error(), errBuf, sizeof(errBuf));
        ALOGE("EVP_PKEY_decrypt[%s]\n", errBuf);
    }
    if (!(cDeStr = (char *) malloc(cDeStrlen))) {
        ALOGE(" (unsigned char *)malloc(cDeStrlen)) failed!\n");
    }
    if ((EVP_PKEY_decrypt(ectx, reinterpret_cast<unsigned char *>(cDeStr), &cDeStrlen,
                          reinterpret_cast<unsigned char *>(cEnStr), cEnstrlen)) != 1) {
        ALOGE(" EVP_PKEY_decrypt failed!\n");
    }
    ALOGI("cDeStrlen:%d\n", cDeStrlen);
    memcpy(deStr, cDeStr, cDeStrlen);
    EVP_PKEY_CTX_free(ectx);
    free(cDeStr);
    return cDeStrlen;
}

int test_my_sm2() {
    ALOGI("test_my_sm2 start");
    //1.首先PC电脑上安装openssl客户端，然后执行下面命令生成公钥-私钥
    //2.生成私钥：openssl ecparam -outform pem -out sm2PriKey.pem -name sm2 -genkey
    //3.生成公钥：openssl ec -in sm2PriKey.pem -pubout -out sm2PubKey.pem
    //4.文本记事本分别打开私钥文件sm2PriKey.pem和公钥文件sm2PriKey.pem，分别复制里面的值给sm2PriKeyStr和sm2PubKeyStr变量
    std::string sm2PriKeyStr = "-----BEGIN SM2 PARAMETERS-----\n"
                               "BggqgRzPVQGCLQ==\n"
                               "-----END SM2 PARAMETERS-----\n"
                               "-----BEGIN PRIVATE KEY-----\n"
                               "MIGIAgEAMBQGCCqBHM9VAYItBggqgRzPVQGCLQRtMGsCAQEEIAeYlDHP36Z3ZQTZ\n"
                               "PwIQSkSU7Ut9uteRHGiGlpxiPGzroUQDQgAEOw+Byzd+Vu31TVCuOQFjewcL4jt4\n"
                               "ShOxGNS0sQaF6g1sBvRwnUbzfaGXdhmkllxCvygGxeX1TF/zI/MQNzgHjg==\n"
                               "-----END PRIVATE KEY-----\n";
    std::string sm2PubKeyStr = "-----BEGIN PUBLIC KEY-----\n"
                               "MFowFAYIKoEcz1UBgi0GCCqBHM9VAYItA0IABDsPgcs3flbt9U1QrjkBY3sHC+I7\n"
                               "eEoTsRjUtLEGheoNbAb0cJ1G832hl3YZpJZcQr8oBsXl9Uxf8yPzEDc4B44=\n"
                               "-----END PUBLIC KEY-----\n";

    unsigned char sm2_en[512], sm2_de[512];
    int sm2enStrLen, sm2deStrLen;


    unsigned char source[20] = {0x41, 0x12, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10, 0x11,
                                0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x20};

    sm2enStrLen = my_sm2encrpt(sm2PubKeyStr, source, 20, sm2_en);
    ALOGI("sm2enStrLen :%d \n", sm2enStrLen);
    std::string sm2_en_str;
    char buf[100];
    for (int i = 0; i < sm2enStrLen; i++) {
        snprintf(buf, 100, "0x%02x ", sm2_en[i]);
        sm2_en_str.append(buf);
    }
    ALOGI("sm2_en_str :%s\n", sm2_en_str.c_str());

    sm2deStrLen = dencryptStr(sm2PriKeyStr, sm2_en, sm2enStrLen, sm2_de);
    ALOGI("sm2deStrLen :%d \n", sm2deStrLen);
    std::string sm2_de_str;
    for (int i = 0; i < sm2deStrLen; i++) {
        snprintf(buf, 100, "0x%x ", sm2_de[i]);
        sm2_de_str.append(buf);
    }
    ALOGI("sm2_de_str :%s\n", sm2_de_str.c_str());

    ALOGI("test_my_sm2 end");
    return 0;
}

