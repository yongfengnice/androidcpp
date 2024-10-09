//
// Created by 86177 on 2024/10/9.
//

#ifndef ANDROIDCPP_OPENSSL_TOOL_H
#define ANDROIDCPP_OPENSSL_TOOL_H

void openssl_tool_version();

const char *openssl_tool_md5_new(const char *);

void openssl_tool_md5_delete(const char *);

#endif //ANDROIDCPP_OPENSSL_TOOL_H
