 }
 #endif /* MBEDTLS_SSL_DTLS_HELLO_VERIFY */
 
 #if defined(MBEDTLS_KEY_EXCHANGE_SOME_PSK_ENABLED)
 static int ssl_conf_has_psk_or_cb( mbedtls_ssl_config const *conf )
 {
 }
 #endif /* MBEDTLS_SSL_SESSION_TICKETS */
 
 #if defined(MBEDTLS_SSL_DTLS_SRTP)
 static int ssl_parse_use_srtp_ext( mbedtls_ssl_context *ssl,
                                    const unsigned char *buf,
                           const mbedtls_ssl_ciphersuite_t * ciphersuite_info )
 {
     mbedtls_ssl_key_cert *cur, *list;
#if defined(MBEDTLS_USE_PSA_CRYPTO)
    psa_algorithm_t pk_alg =
        mbedtls_ssl_get_ciphersuite_sig_pk_psa_alg( ciphersuite_info );
    psa_key_usage_t pk_usage =
        mbedtls_ssl_get_ciphersuite_sig_pk_psa_usage( ciphersuite_info );
#else
     mbedtls_pk_type_t pk_alg =
         mbedtls_ssl_get_ciphersuite_sig_pk_alg( ciphersuite_info );
#endif /* MBEDTLS_USE_PSA_CRYPTO */
     uint32_t flags;
 
 #if defined(MBEDTLS_SSL_SERVER_NAME_INDICATION)
 #endif
         list = ssl->conf->key_cert;
 
#if defined(MBEDTLS_USE_PSA_CRYPTO)
    if( pk_alg == PSA_ALG_NONE )
#else
     if( pk_alg == MBEDTLS_PK_NONE )
#endif /* MBEDTLS_USE_PSA_CRYPTO */
         return( 0 );
 
     MBEDTLS_SSL_DEBUG_MSG( 3, ( "ciphersuite requires certificate" ) );
         MBEDTLS_SSL_DEBUG_CRT( 3, "candidate certificate chain, certificate",
                           cur->cert );
 
#if defined(MBEDTLS_USE_PSA_CRYPTO)
#if defined(MBEDTLS_SSL_ASYNC_PRIVATE)
        if( ( ssl->conf->f_async_sign_start == NULL &&
              ssl->conf->f_async_decrypt_start == NULL &&
              ! mbedtls_pk_can_do_ext( cur->key, pk_alg, pk_usage ) ) ||
            ! mbedtls_pk_can_do_ext( &cur->cert->pk, pk_alg, pk_usage ) )
#else
        if( ! mbedtls_pk_can_do_ext( cur->key, pk_alg, pk_usage ) )
#endif /* MBEDTLS_SSL_ASYNC_PRIVATE */
#else
         if( ! mbedtls_pk_can_do( &cur->cert->pk, pk_alg ) )
#endif /* MBEDTLS_USE_PSA_CRYPTO */
         {
             MBEDTLS_SSL_DEBUG_MSG( 3, ( "certificate mismatch: key type" ) );
             continue;
     }
 #endif
 
 #if defined(MBEDTLS_X509_CRT_PARSE_C)
     /*
      * Final check: if ciphersuite requires us to have a
     }
 #endif
 
#if defined(MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED)
    /* If the ciphersuite requires signing, check whether
     * a suitable hash algorithm is present. */
    sig_type = mbedtls_ssl_get_ciphersuite_sig_alg( suite_info );
    if( sig_type != MBEDTLS_PK_NONE &&
        mbedtls_ssl_tls12_get_preferred_hash_for_sig_alg(
            ssl, mbedtls_ssl_sig_from_pk_alg( sig_type ) ) == MBEDTLS_SSL_HASH_NONE )
    {
        MBEDTLS_SSL_DEBUG_MSG( 3, ( "ciphersuite mismatch: no suitable hash algorithm "
                                    "for signature algorithm %u", (unsigned) sig_type ) );
        return( 0 );
    }

#endif /* MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED */

     *ciphersuite_info = suite_info;
     return( 0 );
 }
 #if defined(MBEDTLS_SSL_SERVER_NAME_INDICATION)
             case MBEDTLS_TLS_EXT_SERVERNAME:
                 MBEDTLS_SSL_DEBUG_MSG( 3, ( "found ServerName extension" ) );
                ret = mbedtls_ssl_parse_server_name_ext( ssl, ext + 4,
                                                         ext + 4 + ext_size );
                 if( ret != 0 )
                     return( ret );
                 break;
             case MBEDTLS_TLS_EXT_ALPN:
                 MBEDTLS_SSL_DEBUG_MSG( 3, ( "found alpn extension" ) );
 
                ret = mbedtls_ssl_parse_alpn_ext( ssl, ext + 4,
                                                  ext + 4 + ext_size );
                 if( ret != 0 )
                     return( ret );
                 break;
 }
 #endif /* MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED */
 
 #if defined(MBEDTLS_SSL_DTLS_SRTP ) && defined(MBEDTLS_SSL_PROTO_DTLS)
 static void ssl_write_use_srtp_ext( mbedtls_ssl_context *ssl,
                                     unsigned char *buf,
 #endif
 
 #if defined(MBEDTLS_SSL_ALPN)
    unsigned char *end = buf + MBEDTLS_SSL_OUT_CONTENT_LEN - 4;
    mbedtls_ssl_write_alpn_ext( ssl, p + 2 + ext_len, end, &olen );
     ext_len += olen;
 #endif
 
          *       `mbedtls_ssl_conf_ca_cb()`, then the
          *       CertificateRequest is currently left empty. */
 
#if defined(MBEDTLS_KEY_EXCHANGE_CERT_REQ_ALLOWED_ENABLED)
#if defined(MBEDTLS_SSL_SERVER_NAME_INDICATION)
        if( ssl->handshake->dn_hints != NULL )
            crt = ssl->handshake->dn_hints;
        else
#endif
        if( ssl->conf->dn_hints != NULL )
            crt = ssl->conf->dn_hints;
        else
#endif
 #if defined(MBEDTLS_SSL_SERVER_NAME_INDICATION)
         if( ssl->handshake->sni_ca_chain != NULL )
             crt = ssl->handshake->sni_ca_chain;