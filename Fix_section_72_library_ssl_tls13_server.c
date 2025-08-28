                 & MBEDTLS_SSL_EXT_SERVERNAME ) > 0 ) ?
                 "TRUE" : "FALSE" ) );
 #endif /* MBEDTLS_SSL_SERVER_NAME_INDICATION */
#if defined ( MBEDTLS_SSL_ALPN )
    MBEDTLS_SSL_DEBUG_MSG( 3,
            ( "- ALPN_EXTENSION   ( %s )",
            ( ( ssl->handshake->extensions_present
                & MBEDTLS_SSL_EXT_ALPN ) > 0 ) ?
                "TRUE" : "FALSE" ) );
#endif /* MBEDTLS_SSL_ALPN */
 }
 #endif /* MBEDTLS_DEBUG_C */
 
     return( 1 );
 }
 
#if defined(MBEDTLS_X509_CRT_PARSE_C) && \
    defined(MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED)
/*
 * Pick best ( private key, certificate chain ) pair based on the signature
 * algorithms supported by the client.
 */
static int ssl_tls13_pick_key_cert( mbedtls_ssl_context *ssl )
{
    mbedtls_ssl_key_cert *key_cert, *key_cert_list;
    const uint16_t *sig_alg = ssl->handshake->received_sig_algs;

#if defined(MBEDTLS_SSL_SERVER_NAME_INDICATION)
    if( ssl->handshake->sni_key_cert != NULL )
        key_cert_list = ssl->handshake->sni_key_cert;
    else
#endif /* MBEDTLS_SSL_SERVER_NAME_INDICATION */
        key_cert_list = ssl->conf->key_cert;

    if( key_cert_list == NULL )
    {
        MBEDTLS_SSL_DEBUG_MSG( 3, ( "server has no certificate" ) );
        return( -1 );
    }

    for( ; *sig_alg != MBEDTLS_TLS1_3_SIG_NONE; sig_alg++ )
    {
        for( key_cert = key_cert_list; key_cert != NULL;
             key_cert = key_cert->next )
        {
            MBEDTLS_SSL_DEBUG_CRT( 3, "certificate (chain) candidate",
                                   key_cert->cert );

            /*
            * This avoids sending the client a cert it'll reject based on
            * keyUsage or other extensions.
            */
            if( mbedtls_x509_crt_check_key_usage(
                    key_cert->cert, MBEDTLS_X509_KU_DIGITAL_SIGNATURE ) != 0 ||
                mbedtls_x509_crt_check_extended_key_usage(
                    key_cert->cert, MBEDTLS_OID_SERVER_AUTH,
                    MBEDTLS_OID_SIZE( MBEDTLS_OID_SERVER_AUTH ) ) != 0 )
            {
                MBEDTLS_SSL_DEBUG_MSG( 3, ( "certificate mismatch: "
                                       "(extended) key usage extension" ) );
                continue;
            }

            MBEDTLS_SSL_DEBUG_MSG( 3,
                                   ( "ssl_tls13_pick_key_cert:"
                                     "check signature algorithm %s [%04x]",
                                     mbedtls_ssl_sig_alg_to_str( *sig_alg ),
                                     *sig_alg ) );
            if( mbedtls_ssl_tls13_check_sig_alg_cert_key_match(
                                            *sig_alg, &key_cert->cert->pk ) )
            {
                ssl->handshake->key_cert = key_cert;
                MBEDTLS_SSL_DEBUG_MSG( 3,
                                       ( "ssl_tls13_pick_key_cert:"
                                         "selected signature algorithm"
                                         " %s [%04x]",
                                         mbedtls_ssl_sig_alg_to_str( *sig_alg ),
                                         *sig_alg ) );
                MBEDTLS_SSL_DEBUG_CRT(
                        3, "selected certificate (chain)",
                        ssl->handshake->key_cert->cert );
                return( 0 );
            }
        }
    }

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "ssl_tls13_pick_key_cert:"
                                "no suitable certificate found" ) );
    return( -1 );
}
#endif /* MBEDTLS_X509_CRT_PARSE_C &&
          MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED */

 /*
  *
  * STATE HANDLING: ClientHello
 
         switch( extension_type )
         {
#if defined(MBEDTLS_SSL_SERVER_NAME_INDICATION)
            case MBEDTLS_TLS_EXT_SERVERNAME:
                MBEDTLS_SSL_DEBUG_MSG( 3, ( "found ServerName extension" ) );
                ret = mbedtls_ssl_parse_server_name_ext( ssl, p,
                                                         extension_data_end );
                if( ret != 0 )
                {
                    MBEDTLS_SSL_DEBUG_RET(
                            1, "mbedtls_ssl_parse_servername_ext", ret );
                    return( ret );
                }
                ssl->handshake->extensions_present |= MBEDTLS_SSL_EXT_SERVERNAME;
                break;
#endif /* MBEDTLS_SSL_SERVER_NAME_INDICATION */

 #if defined(MBEDTLS_ECDH_C)
             case MBEDTLS_TLS_EXT_SUPPORTED_GROUPS:
                 MBEDTLS_SSL_DEBUG_MSG( 3, ( "found supported group extension" ) );
                 ssl->handshake->extensions_present |= MBEDTLS_SSL_EXT_SUPPORTED_VERSIONS;
                 break;
 
#if defined(MBEDTLS_SSL_ALPN)
            case MBEDTLS_TLS_EXT_ALPN:
                MBEDTLS_SSL_DEBUG_MSG( 3, ( "found alpn extension" ) );

                ret = mbedtls_ssl_parse_alpn_ext( ssl, p, extension_data_end );
                if( ret != 0 )
                {
                    MBEDTLS_SSL_DEBUG_RET(
                            1, ( "mbedtls_ssl_parse_alpn_ext" ), ret );
                    return( ret );
                }
                ssl->handshake->extensions_present |= MBEDTLS_SSL_EXT_ALPN;
                break;
#endif /* MBEDTLS_SSL_ALPN */

 #if defined(MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED)
             case MBEDTLS_TLS_EXT_SIG_ALG:
                 MBEDTLS_SSL_DEBUG_MSG( 3, ( "found signature_algorithms extension" ) );
     ssl_tls13_debug_print_client_hello_exts( ssl );
 #endif /* MBEDTLS_DEBUG_C */
 
    return( hrr_required ? SSL_CLIENT_HELLO_HRR_REQUIRED : SSL_CLIENT_HELLO_OK );
}

/* Update the handshake state machine */

static int ssl_tls13_postprocess_client_hello( mbedtls_ssl_context* ssl )
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;

     /*
      * Here we only support the ephemeral or (EC)DHE key echange mode
      */
     if( !ssl_tls13_check_ephemeral_key_exchange( ssl ) )
     {
         MBEDTLS_SSL_DEBUG_MSG(
         return( MBEDTLS_ERR_SSL_ILLEGAL_PARAMETER );
     }
 
    /*
     * Server certificate selection
     */
    if( ssl->conf->f_cert_cb && ( ret = ssl->conf->f_cert_cb( ssl ) ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_RET( 1, "f_cert_cb", ret );
        return( ret );
    }
#if defined(MBEDTLS_SSL_SERVER_NAME_INDICATION)
    ssl->handshake->sni_name = NULL;
    ssl->handshake->sni_name_len = 0;
#endif /* MBEDTLS_SSL_SERVER_NAME_INDICATION */
 
     ret = mbedtls_ssl_tls13_key_schedule_stage_early( ssl );
     if( ret != 0 )
      * - extension_data_length  (2 bytes)
      * - selected_group         (2 bytes)
      */
    MBEDTLS_SSL_CHK_BUF_PTR( buf, end, 6 );
 
     MBEDTLS_PUT_UINT16_BE( MBEDTLS_TLS_EXT_KEY_SHARE, buf, 0 );
     MBEDTLS_PUT_UINT16_BE( 2, buf, 2 );
         return( ret );
     }
 
     return( ret );
 }
 
 
     MBEDTLS_SSL_PROC_CHK( ssl_tls13_finalize_write_server_hello( ssl ) );
 
#if defined(MBEDTLS_SSL_TLS1_3_COMPATIBILITY_MODE)
    /* The server sends a dummy change_cipher_spec record immediately
     * after its first handshake message. This may either be after
     * a ServerHello or a HelloRetryRequest.
     */
    mbedtls_ssl_handshake_set_state(
            ssl, MBEDTLS_SSL_SERVER_CCS_AFTER_SERVER_HELLO );
#else
     mbedtls_ssl_handshake_set_state( ssl, MBEDTLS_SSL_ENCRYPTED_EXTENSIONS );
#endif /* MBEDTLS_SSL_TLS1_3_COMPATIBILITY_MODE */
 
 cleanup:
 
 /*
  * Handler for MBEDTLS_SSL_HELLO_RETRY_REQUEST
  */
static int ssl_tls13_prepare_hello_retry_request( mbedtls_ssl_context *ssl )
 {
     int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
     if( ssl->handshake->hello_retry_request_count > 0 )
 
     MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> write hello retry request" ) );
 
    MBEDTLS_SSL_PROC_CHK( ssl_tls13_prepare_hello_retry_request( ssl ) );
 
     MBEDTLS_SSL_PROC_CHK( mbedtls_ssl_start_handshake_msg(
                               ssl, MBEDTLS_SSL_HS_SERVER_HELLO,
 
     ssl->handshake->hello_retry_request_count++;
 
#if defined(MBEDTLS_SSL_TLS1_3_COMPATIBILITY_MODE)
    /* The server sends a dummy change_cipher_spec record immediately
     * after its first handshake message. This may either be after
     * a ServerHello or a HelloRetryRequest.
     */
    mbedtls_ssl_handshake_set_state(
            ssl, MBEDTLS_SSL_SERVER_CCS_AFTER_HELLO_RETRY_REQUEST );
#else
     mbedtls_ssl_handshake_set_state( ssl, MBEDTLS_SSL_CLIENT_HELLO );
#endif /* MBEDTLS_SSL_TLS1_3_COMPATIBILITY_MODE */
 
 cleanup:
     MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= write hello retry request" ) );
                                                       unsigned char *end,
                                                       size_t *out_len )
 {
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
     unsigned char *p = buf;
     size_t extensions_len = 0;
     unsigned char *p_extensions_len;
    size_t output_len;
 
     *out_len = 0;
 
     p += 2;
 
     ((void) ssl);
    ((void) ret);
    ((void) output_len);

#if defined(MBEDTLS_SSL_ALPN)
    ret = mbedtls_ssl_write_alpn_ext( ssl, p, end, &output_len );
    if( ret != 0 )
        return( ret );
    p += output_len;
#endif /* MBEDTLS_SSL_ALPN */
 
     extensions_len = ( p - p_extensions_len ) - 2;
     MBEDTLS_PUT_UINT16_BE( extensions_len, p_extensions_len, 0 );
     unsigned char *buf;
     size_t buf_len, msg_len;
 
    mbedtls_ssl_set_outbound_transform( ssl,
                                        ssl->handshake->transform_handshake );
    MBEDTLS_SSL_DEBUG_MSG(
        3, ( "switching to handshake transform for outbound data" ) );

     MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> write encrypted extensions" ) );
 
     MBEDTLS_SSL_PROC_CHK( mbedtls_ssl_start_handshake_msg( ssl,
 {
     int authmode;
 
#if defined(MBEDTLS_SSL_SERVER_NAME_INDICATION)
    if( ssl->handshake->sni_authmode != MBEDTLS_SSL_VERIFY_UNSET )
        authmode = ssl->handshake->sni_authmode;
    else
#endif
     authmode = ssl->conf->authmode;
 
     if( authmode == MBEDTLS_SSL_VERIFY_NONE )
 static int ssl_tls13_write_server_certificate( mbedtls_ssl_context *ssl )
 {
     int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;

#if defined(MBEDTLS_X509_CRT_PARSE_C)
    if( ( ssl_tls13_pick_key_cert( ssl ) != 0 ) ||
          mbedtls_ssl_own_cert( ssl ) == NULL )
     {
         MBEDTLS_SSL_DEBUG_MSG( 2, ( "No certificate available." ) );
         MBEDTLS_SSL_PEND_FATAL_ALERT( MBEDTLS_SSL_ALERT_MSG_HANDSHAKE_FAILURE,
                                       MBEDTLS_ERR_SSL_HANDSHAKE_FAILURE);
         return( MBEDTLS_ERR_SSL_HANDSHAKE_FAILURE );
     }
#endif /* MBEDTLS_X509_CRT_PARSE_C */
 
     ret = mbedtls_ssl_tls13_write_certificate( ssl );
     if( ret != 0 )
         return( ret );
     }
 
    MBEDTLS_SSL_DEBUG_MSG( 1, ( "Switch to handshake keys for inbound traffic" ) );
    mbedtls_ssl_set_inbound_transform( ssl, ssl->handshake->transform_handshake );

     if( ssl->handshake->certificate_request_sent )
         mbedtls_ssl_handshake_set_state( ssl, MBEDTLS_SSL_CLIENT_CERTIFICATE );
     else
    {
        MBEDTLS_SSL_DEBUG_MSG( 2, ( "skip parse certificate" ) );
        MBEDTLS_SSL_DEBUG_MSG( 2, ( "skip parse certificate verify" ) );
         mbedtls_ssl_handshake_set_state( ssl, MBEDTLS_SSL_CLIENT_FINISHED );
    }

     return( 0 );
 }
 
 {
     int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
 
     ret = mbedtls_ssl_tls13_process_finished_message( ssl );
     if( ret != 0 )
         return( ret );
             break;
 #endif /* MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED */
 
        /*
         * Injection of dummy-CCS's for middlebox compatibility
         */
#if defined(MBEDTLS_SSL_TLS1_3_COMPATIBILITY_MODE)
        case MBEDTLS_SSL_SERVER_CCS_AFTER_HELLO_RETRY_REQUEST:
            ret = mbedtls_ssl_tls13_write_change_cipher_spec( ssl );
            if( ret == 0 )
                mbedtls_ssl_handshake_set_state( ssl, MBEDTLS_SSL_CLIENT_HELLO );
            break;

        case MBEDTLS_SSL_SERVER_CCS_AFTER_SERVER_HELLO:
            ret = mbedtls_ssl_tls13_write_change_cipher_spec( ssl );
            if( ret == 0 )
                mbedtls_ssl_handshake_set_state( ssl, MBEDTLS_SSL_ENCRYPTED_EXTENSIONS );
            break;
#endif /* MBEDTLS_SSL_TLS1_3_COMPATIBILITY_MODE */

         case MBEDTLS_SSL_SERVER_FINISHED:
             ret = ssl_tls13_write_server_finished( ssl );
             break;
                         ssl, MBEDTLS_SSL_CLIENT_CERTIFICATE_VERIFY );
                 }
                 else
                {
                    MBEDTLS_SSL_DEBUG_MSG( 2, ( "skip parse certificate verify" ) );
                     mbedtls_ssl_handshake_set_state(
                         ssl, MBEDTLS_SSL_CLIENT_FINISHED );
                }
             }
             break;
 