//
// Created by 86177 on 2024/10/9.
//

#include "openssl_tool.h"
#include "log/android_log.h"
#include "openssl/crypto.h"
#include "openssl/md5.h"
#include "openssl/err.h"
#include "openssl/x509.h"
#include "openssl/rsa.h"
#include "openssl/crypto.h"
#include "openssl/pem.h"
#include "openssl/ssl.h"
#include "openssl/err.h"
#include <string.h>

void openssl_tool_version() {
    const char *openssl_version = OpenSSL_version(OPENSSL_VERSION);
    ALOGI("cmd5_calculate_md5 openssl_version=%s", openssl_version);
}

const char *openssl_tool_md5_new(const char *data) {
    unsigned char digest[MD5_DIGEST_LENGTH];
    int i;
    char tmp[3] = {'\0'};
    char *buf = malloc(33);
    if (buf == NULL) {
        return NULL;
    }
    memset(buf, 0, sizeof(buf));

    MD5((const unsigned char *) data, strlen(data), digest);
    for (i = 0; i < MD5_DIGEST_LENGTH; i++) {
        sprintf(tmp, "%2.2x", digest[i]);
        strcat(buf, tmp);
    }
    ALOGI("cmd5_calculate_md5 openssl_tool_md5=%s", buf);
    return buf;
}

void openssl_tool_md5_delete(const char *ptr) {
    if (ptr != NULL) {
        free(ptr);
    }
}
