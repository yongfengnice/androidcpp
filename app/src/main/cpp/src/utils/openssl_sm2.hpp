//
// Created by 86177 on 2024/11/26.
//

#ifndef ANDROIDCPP_OPENSSL_SM2_HPP
#define ANDROIDCPP_OPENSSL_SM2_HPP

#ifdef __cplusplus
extern "C" {
#endif


int my_sm2encrpt(std::string keystr, unsigned char *sourStr, int cStrlen, unsigned char *enStr);

int dencryptStr(std::string keystr, unsigned char *cEnStr, int cEnstrlen, unsigned char *deStr);

int test_my_sm2();


#ifdef __cplusplus
}
#endif

#endif //ANDROIDCPP_OPENSSL_SM2_HPP
