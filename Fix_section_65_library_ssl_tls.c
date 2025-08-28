     else
 #endif /* MBEDTLS_SSL_PROTO_TLS1_2 */
     {
         ssl->handshake->sig_algs_heap_allocated = 0;
     }
#endif /* !MBEDTLS_DEPRECATED_REMOVED */
 #endif /* MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED */
     return( 0 );
 }
     ssl->handshake->sni_ca_crl     = ca_crl;
 }
 
#if defined(MBEDTLS_KEY_EXCHANGE_CERT_REQ_ALLOWED_ENABLED)
void mbedtls_ssl_set_hs_dn_hints( mbedtls_ssl_context *ssl,
                                  const mbedtls_x509_crt *crt)
{
    ssl->handshake->dn_hints = crt;
}
#endif /* MBEDTLS_KEY_EXCHANGE_CERT_REQ_ALLOWED_ENABLED */

 void mbedtls_ssl_set_hs_authmode( mbedtls_ssl_context *ssl,
                                   int authmode )
 {
     memset( conf, 0, sizeof( mbedtls_ssl_config ) );
 }
 
 /* The selection should be the same as mbedtls_x509_crt_profile_default in
  * x509_crt.c, plus Montgomery curves for ECDHE. Here, the order matters:
  * curves with a lower resource usage come first.
 };
 
 #if defined(MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED)
 
 /* NOTICE:
  *   For ssl_preset_*_sig_algs and ssl_tls12_preset_*_sig_algs, the following
  *   - But if there is a good reason, do not change the order of the algorithms.
  *   - ssl_tls12_present* is for TLS 1.2 use only.
  *   - ssl_preset_* is for TLS 1.3 only or hybrid TLS 1.3/1.2 handshakes.
 *
 *   When GnuTLS/Openssl server is configured in TLS 1.2 mode with a certificate
 *   declaring an RSA public key and Mbed TLS is configured in hybrid mode, if
 *   `rsa_pss_rsae_*` algorithms are before `rsa_pkcs1_*` ones in this list then
 *   the GnuTLS/Openssl server chooses an `rsa_pss_rsae_*` signature algorithm
 *   for its signature in the key exchange message. As Mbed TLS 1.2 does not
 *   support them, the handshake fails.
  */
 static uint16_t ssl_preset_default_sig_algs[] = {
 
 #endif /* MBEDTLS_ECDSA_C && MBEDTLS_SHA384_C &&
           MBEDTLS_ECP_DP_SECP521R1_ENABLED */
 
 #if defined(MBEDTLS_RSA_C) &&  defined(MBEDTLS_SHA512_C)
     MBEDTLS_TLS1_3_SIG_RSA_PKCS1_SHA512,
 #endif /* MBEDTLS_RSA_C && MBEDTLS_SHA512_C */
     MBEDTLS_TLS1_3_SIG_RSA_PKCS1_SHA256,
 #endif /* MBEDTLS_RSA_C && MBEDTLS_SHA256_C */
 
#if defined(MBEDTLS_X509_RSASSA_PSS_SUPPORT) && defined(MBEDTLS_SHA512_C)
    MBEDTLS_TLS1_3_SIG_RSA_PSS_RSAE_SHA512,
#endif /* MBEDTLS_X509_RSASSA_PSS_SUPPORT && MBEDTLS_SHA512_C */

#if defined(MBEDTLS_X509_RSASSA_PSS_SUPPORT) && defined(MBEDTLS_SHA384_C)
    MBEDTLS_TLS1_3_SIG_RSA_PSS_RSAE_SHA384,
#endif /* MBEDTLS_X509_RSASSA_PSS_SUPPORT && MBEDTLS_SHA384_C */

#if defined(MBEDTLS_X509_RSASSA_PSS_SUPPORT) && defined(MBEDTLS_SHA256_C)
    MBEDTLS_TLS1_3_SIG_RSA_PSS_RSAE_SHA256,
#endif /* MBEDTLS_X509_RSASSA_PSS_SUPPORT && MBEDTLS_SHA256_C */

     MBEDTLS_TLS_SIG_NONE
 };
 
 #endif
 
 #if defined(MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED)
 #if defined(MBEDTLS_SSL_PROTO_TLS1_2)
             if( mbedtls_ssl_conf_is_tls12_only( conf ) )
                 conf->sig_algs = ssl_tls12_preset_suiteb_sig_algs;
 #endif
 
 #if defined(MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED)
 #if defined(MBEDTLS_SSL_PROTO_TLS1_2)
             if( mbedtls_ssl_conf_is_tls12_only( conf ) )
                 conf->sig_algs = ssl_tls12_preset_default_sig_algs;
         MBEDTLS_SSL_CHK_BUF_READ_PTR( p, supported_sig_algs_end, 2 );
         sig_alg = MBEDTLS_GET_UINT16_BE( p, 0 );
         p += 2;
        MBEDTLS_SSL_DEBUG_MSG( 4, ( "received signature algorithm: 0x%x %s",
                                    sig_alg,
                                    mbedtls_ssl_sig_alg_to_str( sig_alg ) ) );
#if defined(MBEDTLS_SSL_PROTO_TLS1_2)
        if( ssl->tls_version == MBEDTLS_SSL_VERSION_TLS1_2 &&
            ( ! ( mbedtls_ssl_sig_alg_is_supported( ssl, sig_alg ) &&
                  mbedtls_ssl_sig_alg_is_offered( ssl, sig_alg ) ) ) )
        {
             continue;
        }
#endif /* MBEDTLS_SSL_PROTO_TLS1_2 */

        MBEDTLS_SSL_DEBUG_MSG( 4, ( "valid signature algorithm: %s",
                                    mbedtls_ssl_sig_alg_to_str( sig_alg ) ) );
 
         if( common_idx + 1 < MBEDTLS_RECEIVED_SIG_ALGS_SIZE )
         {
         ssl->in_msg[0]  == MBEDTLS_SSL_HS_CERTIFICATE   &&
         memcmp( ssl->in_msg + mbedtls_ssl_hs_hdr_len( ssl ), "\0\0\0", 3 ) == 0 )
     {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "peer has no certificate" ) );
         return( 0 );
     }
     return( -1 );
 
     for( i = 0; received_sig_algs[i] != MBEDTLS_TLS_SIG_NONE; i++ )
     {
        unsigned int hash_alg_received =
                    MBEDTLS_SSL_TLS12_HASH_ALG_FROM_SIG_AND_HASH_ALG(
                        received_sig_algs[i] );
        unsigned int sig_alg_received =
                    MBEDTLS_SSL_TLS12_SIG_ALG_FROM_SIG_AND_HASH_ALG(
                        received_sig_algs[i] );

        if( sig_alg == sig_alg_received )
        {
#if defined(MBEDTLS_USE_PSA_CRYPTO)
            if( ssl->handshake->key_cert && ssl->handshake->key_cert->key )
            {
                psa_algorithm_t psa_hash_alg =
                                mbedtls_psa_translate_md( hash_alg_received );

                if( sig_alg_received == MBEDTLS_SSL_SIG_ECDSA &&
                    ! mbedtls_pk_can_do_ext( ssl->handshake->key_cert->key,
                                             PSA_ALG_ECDSA( psa_hash_alg ),
                                             PSA_KEY_USAGE_SIGN_HASH ) )
                    continue;

                if( sig_alg_received == MBEDTLS_SSL_SIG_RSA &&
                    ! mbedtls_pk_can_do_ext( ssl->handshake->key_cert->key,
                                             PSA_ALG_RSA_PKCS1V15_SIGN(
                                                            psa_hash_alg ),
                                             PSA_KEY_USAGE_SIGN_HASH ) )
                    continue;
            }
#endif /* MBEDTLS_USE_PSA_CRYPTO */

            return( hash_alg_received );
        }
     }
 
     return( MBEDTLS_SSL_HASH_NONE );
 
     for( ; *sig_alg != MBEDTLS_TLS1_3_SIG_NONE; sig_alg++ )
     {
        MBEDTLS_SSL_DEBUG_MSG( 3, ( "got signature scheme [%x] %s",
                                    *sig_alg,
                                    mbedtls_ssl_sig_alg_to_str( *sig_alg ) ) );
         if( ! mbedtls_ssl_sig_alg_is_supported( ssl, *sig_alg ) )
             continue;
         MBEDTLS_SSL_CHK_BUF_PTR( p, end, 2 );
         MBEDTLS_PUT_UINT16_BE( *sig_alg, p, 0 );
         p += 2;
        MBEDTLS_SSL_DEBUG_MSG( 3, ( "sent signature scheme [%x] %s",
                                    *sig_alg,
                                    mbedtls_ssl_sig_alg_to_str( *sig_alg ) ) );
     }
 
     /* Length of supported_signature_algorithms */
 }
 #endif /* MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED */
 
#if defined(MBEDTLS_SSL_SERVER_NAME_INDICATION)
/*
 * mbedtls_ssl_parse_server_name_ext
 *
 * Structure of server_name extension:
 *
 *  enum {
 *        host_name(0), (255)
 *     } NameType;
 *  opaque HostName<1..2^16-1>;
 *
 *  struct {
 *          NameType name_type;
 *          select (name_type) {
 *             case host_name: HostName;
 *           } name;
 *     } ServerName;
 *  struct {
 *          ServerName server_name_list<1..2^16-1>
 *     } ServerNameList;
 */
int mbedtls_ssl_parse_server_name_ext( mbedtls_ssl_context *ssl,
                                       const unsigned char *buf,
                                       const unsigned char *end )
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    const unsigned char *p = buf;
    size_t server_name_list_len, hostname_len;
    const unsigned char *server_name_list_end;

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "parse ServerName extension" ) );

    MBEDTLS_SSL_CHK_BUF_READ_PTR( p, end, 2 );
    server_name_list_len = MBEDTLS_GET_UINT16_BE( p, 0 );
    p += 2;

    MBEDTLS_SSL_CHK_BUF_READ_PTR( p, end, server_name_list_len );
    server_name_list_end = p + server_name_list_len;
    while( p < server_name_list_end )
    {
        MBEDTLS_SSL_CHK_BUF_READ_PTR( p, server_name_list_end, 3 );
        hostname_len = MBEDTLS_GET_UINT16_BE( p, 1 );
        MBEDTLS_SSL_CHK_BUF_READ_PTR( p, server_name_list_end,
                                      hostname_len + 3 );

        if( p[0] == MBEDTLS_TLS_EXT_SERVERNAME_HOSTNAME )
        {
            /* sni_name is intended to be used only during the parsing of the
             * ClientHello message (it is reset to NULL before the end of
             * the message parsing). Thus it is ok to just point to the
             * reception buffer and not make a copy of it.
             */
            ssl->handshake->sni_name = p + 3;
            ssl->handshake->sni_name_len = hostname_len;
            if( ssl->conf->f_sni == NULL )
                return( 0 );
            ret = ssl->conf->f_sni( ssl->conf->p_sni,
                                    ssl, p + 3, hostname_len );
            if( ret != 0 )
            {
                MBEDTLS_SSL_DEBUG_RET( 1, "ssl_sni_wrapper", ret );
                MBEDTLS_SSL_PEND_FATAL_ALERT( MBEDTLS_SSL_ALERT_MSG_UNRECOGNIZED_NAME,
                                              MBEDTLS_ERR_SSL_UNRECOGNIZED_NAME );
                return( MBEDTLS_ERR_SSL_UNRECOGNIZED_NAME );
            }
            return( 0 );
        }

        p += hostname_len + 3;
    }

    return( 0 );
}
#endif /* MBEDTLS_SSL_SERVER_NAME_INDICATION */

#if defined(MBEDTLS_SSL_ALPN)
int mbedtls_ssl_parse_alpn_ext( mbedtls_ssl_context *ssl,
                                const unsigned char *buf,
                                const unsigned char *end )
{
    const unsigned char *p = buf;
    size_t protocol_name_list_len;
    const unsigned char *protocol_name_list;
    const unsigned char *protocol_name_list_end;
    size_t protocol_name_len;

    /* If ALPN not configured, just ignore the extension */
    if( ssl->conf->alpn_list == NULL )
        return( 0 );

    /*
     * RFC7301, section 3.1
     *      opaque ProtocolName<1..2^8-1>;
     *
     *      struct {
     *          ProtocolName protocol_name_list<2..2^16-1>
     *      } ProtocolNameList;
     */

    /*
     * protocol_name_list_len    2 bytes
     * protocol_name_len         1 bytes
     * protocol_name             >=1 byte
     */
    MBEDTLS_SSL_CHK_BUF_READ_PTR( p, end, 4 );

    protocol_name_list_len = MBEDTLS_GET_UINT16_BE( p, 0 );
    p += 2;
    MBEDTLS_SSL_CHK_BUF_READ_PTR( p, end, protocol_name_list_len );
    protocol_name_list = p;
    protocol_name_list_end = p + protocol_name_list_len;

    /* Validate peer's list (lengths) */
    while( p < protocol_name_list_end )
    {
        protocol_name_len = *p++;
        MBEDTLS_SSL_CHK_BUF_READ_PTR( p, protocol_name_list_end,
                                      protocol_name_len );
        if( protocol_name_len == 0 )
        {
            MBEDTLS_SSL_PEND_FATAL_ALERT(
                MBEDTLS_SSL_ALERT_MSG_ILLEGAL_PARAMETER,
                MBEDTLS_ERR_SSL_ILLEGAL_PARAMETER );
            return( MBEDTLS_ERR_SSL_ILLEGAL_PARAMETER );
        }

        p += protocol_name_len;
    }

    /* Use our order of preference */
    for( const char **alpn = ssl->conf->alpn_list; *alpn != NULL; alpn++ )
    {
        size_t const alpn_len = strlen( *alpn );
        p = protocol_name_list;
        while( p < protocol_name_list_end )
        {
            protocol_name_len = *p++;
            if( protocol_name_len == alpn_len &&
                memcmp( p, *alpn, alpn_len ) == 0 )
            {
                ssl->alpn_chosen = *alpn;
                return( 0 );
            }

            p += protocol_name_len;
        }
    }

    /* If we get here, no match was found */
    MBEDTLS_SSL_PEND_FATAL_ALERT(
            MBEDTLS_SSL_ALERT_MSG_NO_APPLICATION_PROTOCOL,
            MBEDTLS_ERR_SSL_NO_APPLICATION_PROTOCOL );
    return( MBEDTLS_ERR_SSL_NO_APPLICATION_PROTOCOL );
}

int mbedtls_ssl_write_alpn_ext( mbedtls_ssl_context *ssl,
                                unsigned char *buf,
                                unsigned char *end,
                                size_t *out_len )
{
    unsigned char *p = buf;
    size_t protocol_name_len;
    *out_len = 0;

    if( ssl->alpn_chosen == NULL )
    {
        return( 0 );
    }

    protocol_name_len = strlen( ssl->alpn_chosen );
    MBEDTLS_SSL_CHK_BUF_PTR( p, end, 7 + protocol_name_len );

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "server side, adding alpn extension" ) );
    /*
     * 0 . 1    ext identifier
     * 2 . 3    ext length
     * 4 . 5    protocol list length
     * 6 . 6    protocol name length
     * 7 . 7+n  protocol name
     */
    MBEDTLS_PUT_UINT16_BE( MBEDTLS_TLS_EXT_ALPN, p, 0 );

    *out_len = 7 + protocol_name_len;

    MBEDTLS_PUT_UINT16_BE( protocol_name_len + 3, p, 2 );
    MBEDTLS_PUT_UINT16_BE( protocol_name_len + 1, p, 4 );
    /* Note: the length of the chosen protocol has been checked to be less
     * than 255 bytes in `mbedtls_ssl_conf_alpn_protocols`.
     */
    p[6] = MBEDTLS_BYTE_0( protocol_name_len );

    memcpy( p + 7, ssl->alpn_chosen, protocol_name_len );
    return ( 0 );
}
#endif /* MBEDTLS_SSL_ALPN */

 #endif /* MBEDTLS_SSL_TLS_C */