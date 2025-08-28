 
 #if defined(MBEDTLS_X509_CRT_PARSE_C)
 #if defined(MBEDTLS_ECDSA_C) && defined(MBEDTLS_RSA_C)
 #define MBEDTLS_SSL_SIG_ALG( hash ) (( hash << 8 ) | MBEDTLS_SSL_SIG_ECDSA), \
                                     (( hash << 8 ) | MBEDTLS_SSL_SIG_RSA),
 #elif defined(MBEDTLS_ECDSA_C)
 #define MBEDTLS_SSL_SIG_ALG( hash ) (( hash << 8 ) | MBEDTLS_SSL_SIG_ECDSA),
 #elif defined(MBEDTLS_RSA_C)
 #define MBEDTLS_SSL_SIG_ALG( hash ) (( hash << 8 ) | MBEDTLS_SSL_SIG_RSA),
 #else
 #define MBEDTLS_SSL_SIG_ALG( hash )
 #endif
 #endif /* MBEDTLS_X509_REMOVE_INFO */
 }
 #endif /* MBEDTLS_X509_CRT_PARSE_C */