 
 #if defined(MBEDTLS_X509_CRT_PARSE_C)
 #if defined(MBEDTLS_ECDSA_C) && defined(MBEDTLS_RSA_C)
#if defined(MBEDTLS_SSL_PROTO_TLS1_3)
/*
 *   When GnuTLS/Openssl server is configured in TLS 1.2 mode with a certificate
 *   declaring an RSA public key and Mbed TLS is configured in hybrid mode, if
 *   `rsa_pss_rsae_*` algorithms are before `rsa_pkcs1_*` ones in this list then
 *   the GnuTLS/Openssl server chooses an `rsa_pss_rsae_*` signature algorithm
 *   for its signature in the key exchange message. As Mbed TLS 1.2 does not
 *   support them, the handshake fails.
 */
#define MBEDTLS_SSL_SIG_ALG( hash ) (( hash << 8 ) | MBEDTLS_SSL_SIG_ECDSA), \
                                    (( hash << 8 ) | MBEDTLS_SSL_SIG_RSA), \
                                    ( 0x800 | hash ),
#else
 #define MBEDTLS_SSL_SIG_ALG( hash ) (( hash << 8 ) | MBEDTLS_SSL_SIG_ECDSA), \
                                     (( hash << 8 ) | MBEDTLS_SSL_SIG_RSA),
#endif
 #elif defined(MBEDTLS_ECDSA_C)
 #define MBEDTLS_SSL_SIG_ALG( hash ) (( hash << 8 ) | MBEDTLS_SSL_SIG_ECDSA),
 #elif defined(MBEDTLS_RSA_C)
#if defined(MBEDTLS_SSL_PROTO_TLS1_3)
/* See above */
#define MBEDTLS_SSL_SIG_ALG( hash ) (( hash << 8 ) | MBEDTLS_SSL_SIG_RSA), \
                                    ( 0x800 | hash ),
#else
 #define MBEDTLS_SSL_SIG_ALG( hash ) (( hash << 8 ) | MBEDTLS_SSL_SIG_RSA),
#endif
 #else
 #define MBEDTLS_SSL_SIG_ALG( hash )
 #endif
 #endif /* MBEDTLS_X509_REMOVE_INFO */
 }
 #endif /* MBEDTLS_X509_CRT_PARSE_C */

void mbedtls_print_supported_sig_algs( void )
{
    mbedtls_printf( "supported signature algorithms:\n" );
    mbedtls_printf("\trsa_pkcs1_sha256 ");
    mbedtls_printf("rsa_pkcs1_sha384 ");
    mbedtls_printf("rsa_pkcs1_sha512\n");
    mbedtls_printf("\tecdsa_secp256r1_sha256 ");
    mbedtls_printf("ecdsa_secp384r1_sha384 ");
    mbedtls_printf("ecdsa_secp521r1_sha512\n");
    mbedtls_printf("\trsa_pss_rsae_sha256 ");
    mbedtls_printf("rsa_pss_rsae_sha384 ");
    mbedtls_printf("rsa_pss_rsae_sha512\n");
    mbedtls_printf("\trsa_pss_pss_sha256 ");
    mbedtls_printf("rsa_pss_pss_sha384 ");
    mbedtls_printf("rsa_pss_pss_sha512\n");
    mbedtls_printf("\ted25519 ");
    mbedtls_printf("ed448 ");
    mbedtls_printf("rsa_pkcs1_sha1 ");
    mbedtls_printf("ecdsa_sha1\n");
    mbedtls_printf( "\n" );
}