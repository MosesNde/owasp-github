 }
 #endif /* MBEDTLS_SSL_DTLS_HELLO_VERIFY */
 
#if defined(MBEDTLS_SSL_SERVER_NAME_INDICATION)
static int ssl_parse_servername_ext( mbedtls_ssl_context *ssl,
                                     const unsigned char *buf,
                                     size_t len )
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    size_t servername_list_size, hostname_len;
    const unsigned char *p;

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "parse ServerName extension" ) );

    if( len < 2 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
        mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                       MBEDTLS_SSL_ALERT_MSG_DECODE_ERROR );
        return( MBEDTLS_ERR_SSL_DECODE_ERROR );
    }
    servername_list_size = ( ( buf[0] << 8 ) | ( buf[1] ) );
    if( servername_list_size + 2 != len )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
        mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                        MBEDTLS_SSL_ALERT_MSG_DECODE_ERROR );
        return( MBEDTLS_ERR_SSL_DECODE_ERROR );
    }

    p = buf + 2;
    while( servername_list_size > 2 )
    {
        hostname_len = ( ( p[1] << 8 ) | p[2] );
        if( hostname_len + 3 > servername_list_size )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
            mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                            MBEDTLS_SSL_ALERT_MSG_DECODE_ERROR );
            return( MBEDTLS_ERR_SSL_DECODE_ERROR );
        }

        if( p[0] == MBEDTLS_TLS_EXT_SERVERNAME_HOSTNAME )
        {
            ssl->handshake->sni_name = p + 3;
            ssl->handshake->sni_name_len = hostname_len;
            if( ssl->conf->f_sni == NULL )
                return( 0 );

            ret = ssl->conf->f_sni( ssl->conf->p_sni,
                                    ssl, p + 3, hostname_len );
            if( ret != 0 )
            {
                MBEDTLS_SSL_DEBUG_RET( 1, "ssl_sni_wrapper", ret );
                mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                        MBEDTLS_SSL_ALERT_MSG_UNRECOGNIZED_NAME );
                return( MBEDTLS_ERR_SSL_UNRECOGNIZED_NAME );
            }
            return( 0 );
        }

        servername_list_size -= hostname_len + 3;
        p += hostname_len + 3;
    }

    if( servername_list_size != 0 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
        mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                        MBEDTLS_SSL_ALERT_MSG_DECODE_ERROR );
        return( MBEDTLS_ERR_SSL_DECODE_ERROR );
    }

    return( 0 );
}
#endif /* MBEDTLS_SSL_SERVER_NAME_INDICATION */

 #if defined(MBEDTLS_KEY_EXCHANGE_SOME_PSK_ENABLED)
 static int ssl_conf_has_psk_or_cb( mbedtls_ssl_config const *conf )
 {
 }
 #endif /* MBEDTLS_SSL_SESSION_TICKETS */
 
#if defined(MBEDTLS_SSL_ALPN)
static int ssl_parse_alpn_ext( mbedtls_ssl_context *ssl,
                               const unsigned char *buf, size_t len )
{
    size_t list_len, cur_len, ours_len;
    const unsigned char *theirs, *start, *end;
    const char **ours;

    /* If ALPN not configured, just ignore the extension */
    if( ssl->conf->alpn_list == NULL )
        return( 0 );

    /*
     * opaque ProtocolName<1..2^8-1>;
     *
     * struct {
     *     ProtocolName protocol_name_list<2..2^16-1>
     * } ProtocolNameList;
     */

    /* Min length is 2 (list_len) + 1 (name_len) + 1 (name) */
    if( len < 4 )
    {
        mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                        MBEDTLS_SSL_ALERT_MSG_DECODE_ERROR );
        return( MBEDTLS_ERR_SSL_DECODE_ERROR );
    }

    list_len = ( buf[0] << 8 ) | buf[1];
    if( list_len != len - 2 )
    {
        mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                        MBEDTLS_SSL_ALERT_MSG_DECODE_ERROR );
        return( MBEDTLS_ERR_SSL_DECODE_ERROR );
    }

    /*
     * Validate peer's list (lengths)
     */
    start = buf + 2;
    end = buf + len;
    for( theirs = start; theirs != end; theirs += cur_len )
    {
        cur_len = *theirs++;

        /* Current identifier must fit in list */
        if( cur_len > (size_t)( end - theirs ) )
        {
            mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                            MBEDTLS_SSL_ALERT_MSG_DECODE_ERROR );
            return( MBEDTLS_ERR_SSL_DECODE_ERROR );
        }

        /* Empty strings MUST NOT be included */
        if( cur_len == 0 )
        {
            mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                            MBEDTLS_SSL_ALERT_MSG_ILLEGAL_PARAMETER );
            return( MBEDTLS_ERR_SSL_ILLEGAL_PARAMETER );
        }
    }

    /*
     * Use our order of preference
     */
    for( ours = ssl->conf->alpn_list; *ours != NULL; ours++ )
    {
        ours_len = strlen( *ours );
        for( theirs = start; theirs != end; theirs += cur_len )
        {
            cur_len = *theirs++;

            if( cur_len == ours_len &&
                memcmp( theirs, *ours, cur_len ) == 0 )
            {
                ssl->alpn_chosen = *ours;
                return( 0 );
            }
        }
    }

    /* If we get there, no match was found */
    mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                            MBEDTLS_SSL_ALERT_MSG_NO_APPLICATION_PROTOCOL );
    return( MBEDTLS_ERR_SSL_NO_APPLICATION_PROTOCOL );
}
#endif /* MBEDTLS_SSL_ALPN */

 #if defined(MBEDTLS_SSL_DTLS_SRTP)
 static int ssl_parse_use_srtp_ext( mbedtls_ssl_context *ssl,
                                    const unsigned char *buf,
                           const mbedtls_ssl_ciphersuite_t * ciphersuite_info )
 {
     mbedtls_ssl_key_cert *cur, *list;
     mbedtls_pk_type_t pk_alg =
         mbedtls_ssl_get_ciphersuite_sig_pk_alg( ciphersuite_info );
     uint32_t flags;
 
 #if defined(MBEDTLS_SSL_SERVER_NAME_INDICATION)
 #endif
         list = ssl->conf->key_cert;
 
     if( pk_alg == MBEDTLS_PK_NONE )
         return( 0 );
 
     MBEDTLS_SSL_DEBUG_MSG( 3, ( "ciphersuite requires certificate" ) );
         MBEDTLS_SSL_DEBUG_CRT( 3, "candidate certificate chain, certificate",
                           cur->cert );
 
         if( ! mbedtls_pk_can_do( &cur->cert->pk, pk_alg ) )
         {
             MBEDTLS_SSL_DEBUG_MSG( 3, ( "certificate mismatch: key type" ) );
             continue;
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

 #if defined(MBEDTLS_X509_CRT_PARSE_C)
     /*
      * Final check: if ciphersuite requires us to have a
     }
 #endif
 
     *ciphersuite_info = suite_info;
     return( 0 );
 }
 #if defined(MBEDTLS_SSL_SERVER_NAME_INDICATION)
             case MBEDTLS_TLS_EXT_SERVERNAME:
                 MBEDTLS_SSL_DEBUG_MSG( 3, ( "found ServerName extension" ) );
                ret = ssl_parse_servername_ext( ssl, ext + 4, ext_size );
                 if( ret != 0 )
                     return( ret );
                 break;
             case MBEDTLS_TLS_EXT_ALPN:
                 MBEDTLS_SSL_DEBUG_MSG( 3, ( "found alpn extension" ) );
 
                ret = ssl_parse_alpn_ext( ssl, ext + 4, ext_size );
                 if( ret != 0 )
                     return( ret );
                 break;
 }
 #endif /* MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED */
 
#if defined(MBEDTLS_SSL_ALPN )
static void ssl_write_alpn_ext( mbedtls_ssl_context *ssl,
                                unsigned char *buf, size_t *olen )
{
    if( ssl->alpn_chosen == NULL )
    {
        *olen = 0;
        return;
    }

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "server hello, adding alpn extension" ) );

    /*
     * 0 . 1    ext identifier
     * 2 . 3    ext length
     * 4 . 5    protocol list length
     * 6 . 6    protocol name length
     * 7 . 7+n  protocol name
     */
    MBEDTLS_PUT_UINT16_BE( MBEDTLS_TLS_EXT_ALPN, buf, 0);

    *olen = 7 + strlen( ssl->alpn_chosen );

    MBEDTLS_PUT_UINT16_BE( *olen - 4, buf, 2 );

    MBEDTLS_PUT_UINT16_BE( *olen - 6, buf, 4 );

    buf[6] = MBEDTLS_BYTE_0( *olen - 7 );

    memcpy( buf + 7, ssl->alpn_chosen, *olen - 7 );
}
#endif /* MBEDTLS_ECDH_C || MBEDTLS_ECDSA_C */

 #if defined(MBEDTLS_SSL_DTLS_SRTP ) && defined(MBEDTLS_SSL_PROTO_DTLS)
 static void ssl_write_use_srtp_ext( mbedtls_ssl_context *ssl,
                                     unsigned char *buf,
 #endif
 
 #if defined(MBEDTLS_SSL_ALPN)
    ssl_write_alpn_ext( ssl, p + 2 + ext_len, &olen );
     ext_len += olen;
 #endif
 
          *       `mbedtls_ssl_conf_ca_cb()`, then the
          *       CertificateRequest is currently left empty. */
 
 #if defined(MBEDTLS_SSL_SERVER_NAME_INDICATION)
         if( ssl->handshake->sni_ca_chain != NULL )
             crt = ssl->handshake->sni_ca_chain;