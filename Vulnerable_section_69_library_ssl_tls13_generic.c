 #if defined(MBEDTLS_X509_RSASSA_PSS_SUPPORT)
     if( sig_alg == MBEDTLS_PK_RSASSA_PSS )
     {
        const mbedtls_md_info_t* md_info;
         rsassa_pss_options.mgf1_hash_id = md_alg;
        if( ( md_info = mbedtls_md_info_from_type( md_alg ) ) == NULL )
        {
            return( MBEDTLS_ERR_SSL_INTERNAL_ERROR );
        }
        rsassa_pss_options.expected_salt_len = mbedtls_md_get_size( md_info );
         options = (const void*) &rsassa_pss_options;
     }
 #endif /* MBEDTLS_X509_RSASSA_PSS_SUPPORT */
      * from the configuration. */
 #if defined(MBEDTLS_SSL_SRV_C)
     if( ssl->conf->endpoint == MBEDTLS_SSL_IS_SERVER )
        authmode = ssl->conf->authmode;
 #endif
 
     /*
      */
     if( ssl->session_negotiate->peer_cert == NULL )
     {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "peer has not sent a certificate" ) );
 
 #if defined(MBEDTLS_SSL_SRV_C)
         if( ssl->conf->endpoint == MBEDTLS_SSL_IS_SERVER )
         /* Currently, we don't have any certificate extensions defined.
          * Hence, we are sending an empty extension with length zero.
          */
        MBEDTLS_PUT_UINT24_BE( 0, p, 0 );
         p += 2;
     }
 
 /*
  * STATE HANDLING: Output Certificate Verify
  */
static int ssl_tls13_get_sig_alg_from_pk( mbedtls_ssl_context *ssl,
                                          mbedtls_pk_context *own_key,
                                          uint16_t *algorithm )
 {
    mbedtls_pk_type_t sig = mbedtls_ssl_sig_from_pk( own_key );
    /* Determine the size of the key */
    size_t own_key_size = mbedtls_pk_get_bitlen( own_key );
    *algorithm = MBEDTLS_TLS1_3_SIG_NONE;
    ((void) own_key_size);
 
    switch( sig )
     {
#if defined(MBEDTLS_ECDSA_C)
         case MBEDTLS_SSL_SIG_ECDSA:
            switch( own_key_size )
             {
                 case 256:
                    *algorithm = MBEDTLS_TLS1_3_SIG_ECDSA_SECP256R1_SHA256;
                    return( 0 );
                 case 384:
                    *algorithm = MBEDTLS_TLS1_3_SIG_ECDSA_SECP384R1_SHA384;
                    return( 0 );
                 case 521:
                    *algorithm = MBEDTLS_TLS1_3_SIG_ECDSA_SECP521R1_SHA512;
                    return( 0 );
                 default:
                    MBEDTLS_SSL_DEBUG_MSG( 3,
                                           ( "unknown key size: %"
                                             MBEDTLS_PRINTF_SIZET " bits",
                                             own_key_size ) );
                     break;
             }
             break;
#endif /* MBEDTLS_ECDSA_C */
 
#if defined(MBEDTLS_RSA_C)
         case MBEDTLS_SSL_SIG_RSA:
#if defined(MBEDTLS_PKCS1_V21)
#if defined(MBEDTLS_SHA256_C)
            if( own_key_size <= 2048 &&
                mbedtls_ssl_sig_alg_is_received( ssl,
                                    MBEDTLS_TLS1_3_SIG_RSA_PSS_RSAE_SHA256 ) )
            {
                *algorithm = MBEDTLS_TLS1_3_SIG_RSA_PSS_RSAE_SHA256;
                return( 0 );
            }
            else
#endif /* MBEDTLS_SHA256_C */
#if defined(MBEDTLS_SHA384_C)
            if( own_key_size <= 3072 &&
                mbedtls_ssl_sig_alg_is_received( ssl,
                                    MBEDTLS_TLS1_3_SIG_RSA_PSS_RSAE_SHA384 ) )
            {
                *algorithm = MBEDTLS_TLS1_3_SIG_RSA_PSS_RSAE_SHA384;
                return( 0 );
            }
            else
#endif /* MBEDTLS_SHA384_C */
#if defined(MBEDTLS_SHA512_C)
            if( own_key_size <= 4096 &&
                mbedtls_ssl_sig_alg_is_received( ssl,
                                    MBEDTLS_TLS1_3_SIG_RSA_PSS_RSAE_SHA512 ) )
            {
                *algorithm = MBEDTLS_TLS1_3_SIG_RSA_PSS_RSAE_SHA512;
                return( 0 );
            }
            else
#endif /* MBEDTLS_SHA512_C */
#endif /* MBEDTLS_PKCS1_V21 */
#if defined(MBEDTLS_PKCS1_V15)
#if defined(MBEDTLS_SHA256_C)
            if( own_key_size <= 2048 &&
                mbedtls_ssl_sig_alg_is_received( ssl,
                                    MBEDTLS_TLS1_3_SIG_RSA_PKCS1_SHA256 ) )
            {
                *algorithm = MBEDTLS_TLS1_3_SIG_RSA_PKCS1_SHA256;
                return( 0 );
            }
            else
#endif /* MBEDTLS_SHA256_C */
#if defined(MBEDTLS_SHA384_C)
            if( own_key_size <= 3072 &&
                mbedtls_ssl_sig_alg_is_received( ssl,
                                    MBEDTLS_TLS1_3_SIG_RSA_PKCS1_SHA384 ) )
             {
                *algorithm = MBEDTLS_TLS1_3_SIG_RSA_PKCS1_SHA384;
                return( 0 );
            }
            else
#endif /* MBEDTLS_SHA384_C */
#if defined(MBEDTLS_SHA512_C)
            if( own_key_size <= 4096 &&
                mbedtls_ssl_sig_alg_is_received( ssl,
                                    MBEDTLS_TLS1_3_SIG_RSA_PKCS1_SHA512 ) )
            {
                *algorithm = MBEDTLS_TLS1_3_SIG_RSA_PKCS1_SHA512;
                return( 0 );
            }
            else
#endif /* MBEDTLS_SHA512_C */
#endif /* MBEDTLS_PKCS1_V15 */
            {
                MBEDTLS_SSL_DEBUG_MSG( 3,
                                       ( "unknown key size: %"
                                         MBEDTLS_PRINTF_SIZET " bits",
                                         own_key_size ) );
             }
             break;
#endif /* MBEDTLS_RSA_C */
         default:
            MBEDTLS_SSL_DEBUG_MSG( 1,
                                   ( "unknown signature type : %u", sig ) );
             break;
     }
     return( -1 );
 }
 
      *    opaque signature<0..2^16-1>;
      *  } CertificateVerify;
      */
    ret = ssl_tls13_get_sig_alg_from_pk( ssl, own_key, &algorithm );
    if( ret != 0 || ! mbedtls_ssl_sig_alg_is_received( ssl, algorithm ) )
     {
         MBEDTLS_SSL_DEBUG_MSG( 1,
                     ( "signature algorithm not in received or offered list." ) );
         return( MBEDTLS_ERR_SSL_HANDSHAKE_FAILURE );
     }
 
     if( mbedtls_ssl_tls13_get_pk_type_and_md_alg_from_sig_alg(
                                         algorithm, &pk_type, &md_alg ) != 0 )
     {
     mbedtls_ssl_handshake_params *handshake = ssl->handshake;
 
     /* Get size of the TLS opaque key_exchange field of the KeyShareEntry struct. */
    MBEDTLS_SSL_CHK_BUF_PTR( p, end, 2 );
     uint16_t peerkey_len = MBEDTLS_GET_UINT16_BE( p, 0 );
     p += 2;
 
     /* Check if key size is consistent with given buffer length. */
    MBEDTLS_SSL_CHK_BUF_PTR( p, end, peerkey_len );
 
     /* Store peer's ECDH public key. */
     memcpy( handshake->ecdh_psa_peerkey, p, peerkey_len );