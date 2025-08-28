     }
 }
 
#if defined(MBEDTLS_USE_PSA_CRYPTO)
psa_algorithm_t mbedtls_ssl_get_ciphersuite_sig_pk_psa_alg( const mbedtls_ssl_ciphersuite_t *info )
{
    switch( info->key_exchange )
    {
        case MBEDTLS_KEY_EXCHANGE_RSA:
        case MBEDTLS_KEY_EXCHANGE_RSA_PSK:
            return( PSA_ALG_RSA_PKCS1V15_CRYPT );
        case MBEDTLS_KEY_EXCHANGE_DHE_RSA:
        case MBEDTLS_KEY_EXCHANGE_ECDHE_RSA:
            return( PSA_ALG_RSA_PKCS1V15_SIGN(
                        mbedtls_psa_translate_md( info->mac ) ) );

        case MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA:
            return( PSA_ALG_ECDSA( mbedtls_psa_translate_md( info->mac ) ) );

        case MBEDTLS_KEY_EXCHANGE_ECDH_RSA:
        case MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA:
            return( PSA_ALG_ECDH );

        default:
            return( PSA_ALG_NONE );
    }
}

psa_key_usage_t mbedtls_ssl_get_ciphersuite_sig_pk_psa_usage( const mbedtls_ssl_ciphersuite_t *info )
 {
     switch( info->key_exchange )
     {
         case MBEDTLS_KEY_EXCHANGE_RSA:
        case MBEDTLS_KEY_EXCHANGE_RSA_PSK:
            return( PSA_KEY_USAGE_DECRYPT );
        case MBEDTLS_KEY_EXCHANGE_DHE_RSA:
        case MBEDTLS_KEY_EXCHANGE_ECDHE_RSA:
        case MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA:
            return( PSA_KEY_USAGE_SIGN_HASH );

        case MBEDTLS_KEY_EXCHANGE_ECDH_RSA:
        case MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA:
            return( PSA_KEY_USAGE_DERIVE );

        default:
            return( 0 );
    }
}
#endif /* MBEDTLS_USE_PSA_CRYPTO */

mbedtls_pk_type_t mbedtls_ssl_get_ciphersuite_sig_alg( const mbedtls_ssl_ciphersuite_t *info )
{
    switch( info->key_exchange )
    {
         case MBEDTLS_KEY_EXCHANGE_DHE_RSA:
         case MBEDTLS_KEY_EXCHANGE_ECDHE_RSA:
             return( MBEDTLS_PK_RSA );