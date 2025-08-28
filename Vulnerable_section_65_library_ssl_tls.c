     else
 #endif /* MBEDTLS_SSL_PROTO_TLS1_2 */
     {
        ssl->handshake->sig_algs = ssl->conf->sig_algs;
         ssl->handshake->sig_algs_heap_allocated = 0;
     }
#endif /* MBEDTLS_DEPRECATED_REMOVED */
 #endif /* MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED */
     return( 0 );
 }
     ssl->handshake->sni_ca_crl     = ca_crl;
 }
 
 void mbedtls_ssl_set_hs_authmode( mbedtls_ssl_context *ssl,
                                   int authmode )
 {
     memset( conf, 0, sizeof( mbedtls_ssl_config ) );
 }
 
#if defined(MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED)
#if !defined(MBEDTLS_DEPRECATED_REMOVED)
/* The selection should be the same as mbedtls_x509_crt_profile_default in
 * x509_crt.c. Here, the order matters. Currently we favor stronger hashes,
 * for no fundamental reason.
 * See the documentation of mbedtls_ssl_conf_curves() for what we promise
 * about this list. */
static int ssl_preset_default_hashes[] = {
#if defined(MBEDTLS_SHA512_C)
    MBEDTLS_MD_SHA512,
#endif
#if defined(MBEDTLS_SHA384_C)
    MBEDTLS_MD_SHA384,
#endif
#if defined(MBEDTLS_SHA256_C)
    MBEDTLS_MD_SHA256,
#endif
    MBEDTLS_MD_NONE
};
#endif /* !MBEDTLS_DEPRECATED_REMOVED */
#endif /* MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED */

 /* The selection should be the same as mbedtls_x509_crt_profile_default in
  * x509_crt.c, plus Montgomery curves for ECDHE. Here, the order matters:
  * curves with a lower resource usage come first.
 };
 
 #if defined(MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED)
#if !defined(MBEDTLS_DEPRECATED_REMOVED)
static int ssl_preset_suiteb_hashes[] = {
#if defined(MBEDTLS_SHA256_C)
    MBEDTLS_MD_SHA256,
#endif
#if defined(MBEDTLS_SHA384_C)
    MBEDTLS_MD_SHA384,
#endif
    MBEDTLS_MD_NONE
};
#endif /* !MBEDTLS_DEPRECATED_REMOVED */
 
 /* NOTICE:
  *   For ssl_preset_*_sig_algs and ssl_tls12_preset_*_sig_algs, the following
  *   - But if there is a good reason, do not change the order of the algorithms.
  *   - ssl_tls12_present* is for TLS 1.2 use only.
  *   - ssl_preset_* is for TLS 1.3 only or hybrid TLS 1.3/1.2 handshakes.
  */
 static uint16_t ssl_preset_default_sig_algs[] = {
 
 #endif /* MBEDTLS_ECDSA_C && MBEDTLS_SHA384_C &&
           MBEDTLS_ECP_DP_SECP521R1_ENABLED */
 
#if defined(MBEDTLS_X509_RSASSA_PSS_SUPPORT) && defined(MBEDTLS_SHA256_C)
    MBEDTLS_TLS1_3_SIG_RSA_PSS_RSAE_SHA256,
#endif /* MBEDTLS_X509_RSASSA_PSS_SUPPORT && MBEDTLS_SHA256_C */

 #if defined(MBEDTLS_RSA_C) &&  defined(MBEDTLS_SHA512_C)
     MBEDTLS_TLS1_3_SIG_RSA_PKCS1_SHA512,
 #endif /* MBEDTLS_RSA_C && MBEDTLS_SHA512_C */
     MBEDTLS_TLS1_3_SIG_RSA_PKCS1_SHA256,
 #endif /* MBEDTLS_RSA_C && MBEDTLS_SHA256_C */
 
     MBEDTLS_TLS_SIG_NONE
 };
 
 #endif
 
 #if defined(MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED)
#if !defined(MBEDTLS_DEPRECATED_REMOVED)
            conf->sig_hashes = ssl_preset_suiteb_hashes;
#endif /* !MBEDTLS_DEPRECATED_REMOVED */
 #if defined(MBEDTLS_SSL_PROTO_TLS1_2)
             if( mbedtls_ssl_conf_is_tls12_only( conf ) )
                 conf->sig_algs = ssl_tls12_preset_suiteb_sig_algs;
 #endif
 
 #if defined(MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED)
#if !defined(MBEDTLS_DEPRECATED_REMOVED)
            conf->sig_hashes = ssl_preset_default_hashes;
#endif /* !MBEDTLS_DEPRECATED_REMOVED */
 #if defined(MBEDTLS_SSL_PROTO_TLS1_2)
             if( mbedtls_ssl_conf_is_tls12_only( conf ) )
                 conf->sig_algs = ssl_tls12_preset_default_sig_algs;
         MBEDTLS_SSL_CHK_BUF_READ_PTR( p, supported_sig_algs_end, 2 );
         sig_alg = MBEDTLS_GET_UINT16_BE( p, 0 );
         p += 2;

        MBEDTLS_SSL_DEBUG_MSG( 4, ( "received signature algorithm: 0x%x",
                                    sig_alg ) );

        if( ! mbedtls_ssl_sig_alg_is_supported( ssl, sig_alg ) ||
            ! mbedtls_ssl_sig_alg_is_offered( ssl, sig_alg ) )
             continue;
 
         if( common_idx + 1 < MBEDTLS_RECEIVED_SIG_ALGS_SIZE )
         {
         ssl->in_msg[0]  == MBEDTLS_SSL_HS_CERTIFICATE   &&
         memcmp( ssl->in_msg + mbedtls_ssl_hs_hdr_len( ssl ), "\0\0\0", 3 ) == 0 )
     {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "TLSv1 client has no certificate" ) );
         return( 0 );
     }
     return( -1 );
 
     for( i = 0; received_sig_algs[i] != MBEDTLS_TLS_SIG_NONE; i++ )
     {
        if( sig_alg == MBEDTLS_SSL_TLS12_SIG_ALG_FROM_SIG_AND_HASH_ALG(
                            received_sig_algs[i] ) )
            return( MBEDTLS_SSL_TLS12_HASH_ALG_FROM_SIG_AND_HASH_ALG(
                        received_sig_algs[i] ) );
     }
 
     return( MBEDTLS_SSL_HASH_NONE );
 
     for( ; *sig_alg != MBEDTLS_TLS1_3_SIG_NONE; sig_alg++ )
     {
         if( ! mbedtls_ssl_sig_alg_is_supported( ssl, *sig_alg ) )
             continue;
         MBEDTLS_SSL_CHK_BUF_PTR( p, end, 2 );
         MBEDTLS_PUT_UINT16_BE( *sig_alg, p, 0 );
         p += 2;
        MBEDTLS_SSL_DEBUG_MSG( 3, ( "signature scheme [%x]", *sig_alg ) );
     }
 
     /* Length of supported_signature_algorithms */
 }
 #endif /* MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED */
 
 #endif /* MBEDTLS_SSL_TLS_C */