                 & MBEDTLS_SSL_EXT_SERVERNAME ) > 0 ) ?
                 "TRUE" : "FALSE" ) );
 #endif /* MBEDTLS_SSL_SERVER_NAME_INDICATION */
 }
 #endif /* MBEDTLS_DEBUG_C */
 
     return( 1 );
 }
 
 /*
  *
  * STATE HANDLING: ClientHello
 
         switch( extension_type )
         {
 #if defined(MBEDTLS_ECDH_C)
             case MBEDTLS_TLS_EXT_SUPPORTED_GROUPS:
                 MBEDTLS_SSL_DEBUG_MSG( 3, ( "found supported group extension" ) );
                 ssl->handshake->extensions_present |= MBEDTLS_SSL_EXT_SUPPORTED_VERSIONS;
                 break;
 
 #if defined(MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED)
             case MBEDTLS_TLS_EXT_SIG_ALG:
                 MBEDTLS_SSL_DEBUG_MSG( 3, ( "found signature_algorithms extension" ) );
     ssl_tls13_debug_print_client_hello_exts( ssl );
 #endif /* MBEDTLS_DEBUG_C */
 
     /*
      * Here we only support the ephemeral or (EC)DHE key echange mode
      */

     if( !ssl_tls13_check_ephemeral_key_exchange( ssl ) )
     {
         MBEDTLS_SSL_DEBUG_MSG(
         return( MBEDTLS_ERR_SSL_ILLEGAL_PARAMETER );
     }
 
    return( hrr_required ? SSL_CLIENT_HELLO_HRR_REQUIRED : SSL_CLIENT_HELLO_OK );
}

/* Update the handshake state machine */

static int ssl_tls13_postprocess_client_hello( mbedtls_ssl_context* ssl )
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
 
     ret = mbedtls_ssl_tls13_key_schedule_stage_early( ssl );
     if( ret != 0 )
      * - extension_data_length  (2 bytes)
      * - selected_group         (2 bytes)
      */
    MBEDTLS_SSL_CHK_BUF_READ_PTR( buf, end, 6 );
 
     MBEDTLS_PUT_UINT16_BE( MBEDTLS_TLS_EXT_KEY_SHARE, buf, 0 );
     MBEDTLS_PUT_UINT16_BE( 2, buf, 2 );
         return( ret );
     }
 
    mbedtls_ssl_set_outbound_transform( ssl,
                                        ssl->handshake->transform_handshake );
    MBEDTLS_SSL_DEBUG_MSG(
        3, ( "switching to handshake transform for outbound data" ) );

     return( ret );
 }
 
 
     MBEDTLS_SSL_PROC_CHK( ssl_tls13_finalize_write_server_hello( ssl ) );
 
     mbedtls_ssl_handshake_set_state( ssl, MBEDTLS_SSL_ENCRYPTED_EXTENSIONS );
 
 cleanup:
 
 /*
  * Handler for MBEDTLS_SSL_HELLO_RETRY_REQUEST
  */
static int ssl_tls13_write_hello_retry_request_coordinate(
                                                    mbedtls_ssl_context *ssl )
 {
     int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
     if( ssl->handshake->hello_retry_request_count > 0 )
 
     MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> write hello retry request" ) );
 
    MBEDTLS_SSL_PROC_CHK( ssl_tls13_write_hello_retry_request_coordinate( ssl ) );
 
     MBEDTLS_SSL_PROC_CHK( mbedtls_ssl_start_handshake_msg(
                               ssl, MBEDTLS_SSL_HS_SERVER_HELLO,
 
     ssl->handshake->hello_retry_request_count++;
 
     mbedtls_ssl_handshake_set_state( ssl, MBEDTLS_SSL_CLIENT_HELLO );
 
 cleanup:
     MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= write hello retry request" ) );
                                                       unsigned char *end,
                                                       size_t *out_len )
 {
     unsigned char *p = buf;
     size_t extensions_len = 0;
     unsigned char *p_extensions_len;
 
     *out_len = 0;
 
     p += 2;
 
     ((void) ssl);
 
     extensions_len = ( p - p_extensions_len ) - 2;
     MBEDTLS_PUT_UINT16_BE( extensions_len, p_extensions_len, 0 );
     unsigned char *buf;
     size_t buf_len, msg_len;
 
     MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> write encrypted extensions" ) );
 
     MBEDTLS_SSL_PROC_CHK( mbedtls_ssl_start_handshake_msg( ssl,
 {
     int authmode;
 
     authmode = ssl->conf->authmode;
 
     if( authmode == MBEDTLS_SSL_VERIFY_NONE )
 static int ssl_tls13_write_server_certificate( mbedtls_ssl_context *ssl )
 {
     int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    if( mbedtls_ssl_own_cert( ssl ) == NULL )
     {
         MBEDTLS_SSL_DEBUG_MSG( 2, ( "No certificate available." ) );
         MBEDTLS_SSL_PEND_FATAL_ALERT( MBEDTLS_SSL_ALERT_MSG_HANDSHAKE_FAILURE,
                                       MBEDTLS_ERR_SSL_HANDSHAKE_FAILURE);
         return( MBEDTLS_ERR_SSL_HANDSHAKE_FAILURE );
     }
 
     ret = mbedtls_ssl_tls13_write_certificate( ssl );
     if( ret != 0 )
         return( ret );
     }
 
     if( ssl->handshake->certificate_request_sent )
    {
         mbedtls_ssl_handshake_set_state( ssl, MBEDTLS_SSL_CLIENT_CERTIFICATE );

        MBEDTLS_SSL_DEBUG_MSG( 1, ( "Switch to handshake keys for inbound traffic" ) );
        mbedtls_ssl_set_inbound_transform( ssl, ssl->handshake->transform_handshake );
    }
     else
         mbedtls_ssl_handshake_set_state( ssl, MBEDTLS_SSL_CLIENT_FINISHED );
     return( 0 );
 }
 
 {
     int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
 
    if( ! ssl->handshake->certificate_request_sent )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1,
            ( "Switch to handshake traffic keys for inbound traffic" ) );
        mbedtls_ssl_set_inbound_transform( ssl, ssl->handshake->transform_handshake );
    }
     ret = mbedtls_ssl_tls13_process_finished_message( ssl );
     if( ret != 0 )
         return( ret );
             break;
 #endif /* MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED */
 
         case MBEDTLS_SSL_SERVER_FINISHED:
             ret = ssl_tls13_write_server_finished( ssl );
             break;
                         ssl, MBEDTLS_SSL_CLIENT_CERTIFICATE_VERIFY );
                 }
                 else
                     mbedtls_ssl_handshake_set_state(
                         ssl, MBEDTLS_SSL_CLIENT_FINISHED );
             }
             break;
 