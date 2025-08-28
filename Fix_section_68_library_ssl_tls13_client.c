 
 #if defined(MBEDTLS_SSL_ALPN)
 static int ssl_tls13_parse_alpn_ext( mbedtls_ssl_context *ssl,
                                     const unsigned char *buf, size_t len )
 {
     const unsigned char *p = buf;
     const unsigned char *end = buf + len;
    size_t protocol_name_list_len, protocol_name_len;
    const unsigned char *protocol_name_list_end;
 
     /* If we didn't send it, the server shouldn't send it */
     if( ssl->conf->alpn_list == NULL )
      * the "ProtocolNameList" MUST contain exactly one "ProtocolName"
      */
 
    MBEDTLS_SSL_CHK_BUF_READ_PTR( p, end, 2 );
    protocol_name_list_len = MBEDTLS_GET_UINT16_BE( p, 0 );
     p += 2;
 
    MBEDTLS_SSL_CHK_BUF_READ_PTR( p, end, protocol_name_list_len );
    protocol_name_list_end = p + protocol_name_list_len;

    MBEDTLS_SSL_CHK_BUF_READ_PTR( p, protocol_name_list_end, 1 );
    protocol_name_len = *p++;
 
     /* Check that the server chosen protocol was in our list and save it */
    MBEDTLS_SSL_CHK_BUF_READ_PTR( p, protocol_name_list_end, protocol_name_len );
    for( const char **alpn = ssl->conf->alpn_list; *alpn != NULL; alpn++ )
     {
        if( protocol_name_len == strlen( *alpn ) &&
            memcmp( p, *alpn, protocol_name_len ) == 0 )
         {
             ssl->alpn_chosen = *alpn;
             return( 0 );
      * - cipher_suite               2 bytes
      * - legacy_compression_method  1 byte
      */
     MBEDTLS_SSL_CHK_BUF_READ_PTR( p, end, legacy_session_id_echo_len + 4 );
      p += legacy_session_id_echo_len + 4;
 
     /* Case of no extension */
 }
 
 /* Returns a negative value on failure, and otherwise
 * - SSL_SERVER_HELLO or
 * - SSL_SERVER_HELLO_HRR
  * to indicate which message is expected and to be parsed next.
  */
#define SSL_SERVER_HELLO 0
#define SSL_SERVER_HELLO_HRR 1
 static int ssl_server_hello_is_hrr( mbedtls_ssl_context *ssl,
                                     const unsigned char *buf,
                                     const unsigned char *end )
     if( memcmp( buf + 2, mbedtls_ssl_tls13_hello_retry_request_magic,
                 sizeof( mbedtls_ssl_tls13_hello_retry_request_magic ) ) == 0 )
     {
        return( SSL_SERVER_HELLO_HRR );
     }
 
    return( SSL_SERVER_HELLO );
 }
 
/*
  * Returns a negative value on failure, and otherwise
 * - SSL_SERVER_HELLO or
 * - SSL_SERVER_HELLO_HRR or
 * - SSL_SERVER_HELLO_TLS1_2
  */
#define SSL_SERVER_HELLO_TLS1_2 2
static int ssl_tls13_preprocess_server_hello( mbedtls_ssl_context *ssl,
                                              const unsigned char *buf,
                                              const unsigned char *end )
 {
     int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    mbedtls_ssl_handshake_params *handshake = ssl->handshake;
 
     MBEDTLS_SSL_PROC_CHK_NEG( ssl_tls13_is_supported_versions_ext_present(
                                  ssl, buf, end ) );
     if( ret == 0 )
     {
         MBEDTLS_SSL_PROC_CHK_NEG(
            ssl_tls13_is_downgrade_negotiation( ssl, buf, end ) );
 
         /* If the server is negotiating TLS 1.2 or below and:
          * . we did not propose TLS 1.2 or
          * . the server responded it is TLS 1.3 capable but negotiating a lower
          *   version of the protocol and thus we are under downgrade attack
          * abort the handshake with an "illegal parameter" alert.
          */
        if( handshake->min_tls_version > MBEDTLS_SSL_VERSION_TLS1_2 || ret )
         {
             MBEDTLS_SSL_PEND_FATAL_ALERT( MBEDTLS_SSL_ALERT_MSG_ILLEGAL_PARAMETER,
                                           MBEDTLS_ERR_SSL_ILLEGAL_PARAMETER );
         ssl->keep_current_message = 1;
         ssl->tls_version = MBEDTLS_SSL_VERSION_TLS1_2;
         mbedtls_ssl_add_hs_msg_to_checksum( ssl, MBEDTLS_SSL_HS_SERVER_HELLO,
                                            buf, (size_t)(end - buf) );
 
         if( mbedtls_ssl_conf_tls13_some_ephemeral_enabled( ssl ) )
         {
                 return( ret );
         }
 
        return( SSL_SERVER_HELLO_TLS1_2 );
     }
 
    handshake->extensions_present = MBEDTLS_SSL_EXT_NONE;

    ret = ssl_server_hello_is_hrr( ssl, buf, end );
     switch( ret )
     {
        case SSL_SERVER_HELLO:
             MBEDTLS_SSL_DEBUG_MSG( 2, ( "received ServerHello message" ) );
             break;
        case SSL_SERVER_HELLO_HRR:
             MBEDTLS_SSL_DEBUG_MSG( 2, ( "received HelloRetryRequest message" ) );
              /* If a client receives a second
               * HelloRetryRequest in the same connection (i.e., where the ClientHello
               * was itself in response to a HelloRetryRequest), it MUST abort the
               * handshake with an "unexpected_message" alert.
               */
            if( handshake->hello_retry_request_count > 0 )
             {
                 MBEDTLS_SSL_DEBUG_MSG( 1, ( "Multiple HRRs received" ) );
                 MBEDTLS_SSL_PEND_FATAL_ALERT( MBEDTLS_SSL_ALERT_MSG_UNEXPECTED_MESSAGE,
                 return( MBEDTLS_ERR_SSL_ILLEGAL_PARAMETER );
             }
 
            handshake->hello_retry_request_count++;
 
             break;
     }
     MBEDTLS_SSL_DEBUG_MSG( 1, ( "Switch to handshake keys for inbound traffic" ) );
     ssl->session_in = ssl->session_negotiate;
 
 cleanup:
     if( ret != 0 )
     {
 {
     int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
 
     mbedtls_ssl_session_reset_msg_layer( ssl, 0 );
 
     /*
 
     MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> %s", __func__ ) );
 
    MBEDTLS_SSL_PROC_CHK( mbedtls_ssl_tls13_fetch_handshake_msg( ssl,
                                             MBEDTLS_SSL_HS_SERVER_HELLO,
                                             &buf, &buf_len ) );
 
    ret = ssl_tls13_preprocess_server_hello( ssl, buf, buf + buf_len );
     if( ret < 0 )
         goto cleanup;
     else
        is_hrr = ( ret == SSL_SERVER_HELLO_HRR );
 
    if( ret == SSL_SERVER_HELLO_TLS1_2 )
     {
         ret = 0;
         goto cleanup;
                                         buf, buf_len );
 
     if( is_hrr )
    {
         MBEDTLS_SSL_PROC_CHK( ssl_tls13_postprocess_hrr( ssl ) );
#if defined(MBEDTLS_SSL_TLS1_3_COMPATIBILITY_MODE)
    /* If not offering early data, the client sends a dummy CCS record
     * immediately before its second flight. This may either be before
     * its second ClientHello or before its encrypted handshake flight.
     */
        mbedtls_ssl_handshake_set_state( ssl,
            MBEDTLS_SSL_CLIENT_CCS_BEFORE_2ND_CLIENT_HELLO );
#else
        mbedtls_ssl_handshake_set_state( ssl, MBEDTLS_SSL_CLIENT_HELLO );
#endif /* MBEDTLS_SSL_TLS1_3_COMPATIBILITY_MODE */
    }
     else
    {
         MBEDTLS_SSL_PROC_CHK( ssl_tls13_postprocess_server_hello( ssl ) );
        mbedtls_ssl_handshake_set_state( ssl, MBEDTLS_SSL_ENCRYPTED_EXTENSIONS );
    }
 
 cleanup:
     MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= %s ( %s )", __func__,
 
 /*
  *
 * Handler for MBEDTLS_SSL_ENCRYPTED_EXTENSIONS
  *
  * The EncryptedExtensions message contains any extensions which
  * should be protected, i.e., any which are not needed to establish
  * the cryptographic context.
  */
 
 /* Parse EncryptedExtensions message
  * struct {
  *     Extension extensions<0..2^16-1>;
     p += 2;
 
     MBEDTLS_SSL_DEBUG_BUF( 3, "encrypted extensions", p, extensions_len );
     MBEDTLS_SSL_CHK_BUF_READ_PTR( p, end, extensions_len );
    extensions_end = p + extensions_len;
 
     while( p < extensions_end )
     {
     return( ret );
 }
 
static int ssl_tls13_process_encrypted_extensions( mbedtls_ssl_context *ssl )
 {
    int ret;
    unsigned char *buf;
    size_t buf_len;

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> parse encrypted extensions" ) );

    MBEDTLS_SSL_PROC_CHK( mbedtls_ssl_tls13_fetch_handshake_msg( ssl,
                                             MBEDTLS_SSL_HS_ENCRYPTED_EXTENSIONS,
                                             &buf, &buf_len ) );

    /* Process the message contents */
    MBEDTLS_SSL_PROC_CHK(
        ssl_tls13_parse_encrypted_extensions( ssl, buf, buf + buf_len ) );

    mbedtls_ssl_add_hs_msg_to_checksum( ssl, MBEDTLS_SSL_HS_ENCRYPTED_EXTENSIONS,
                                        buf, buf_len );

 #if defined(MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED)
     if( mbedtls_ssl_tls13_some_psk_enabled( ssl ) )
         mbedtls_ssl_handshake_set_state( ssl, MBEDTLS_SSL_SERVER_FINISHED );
     ((void) ssl);
     mbedtls_ssl_handshake_set_state( ssl, MBEDTLS_SSL_SERVER_FINISHED );
 #endif

cleanup:

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= parse encrypted extensions" ) );
    return( ret );

 }
 
 #if defined(MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED)
 /*
  * STATE HANDLING: CertificateRequest
  *
  */
     if( ( ssl->in_msgtype == MBEDTLS_SSL_MSG_HANDSHAKE ) &&
         ( ssl->in_msg[0] == MBEDTLS_SSL_HS_CERTIFICATE_REQUEST ) )
     {
        MBEDTLS_SSL_DEBUG_MSG( 3, ( "got a certificate request" ) );
         return( SSL_CERTIFICATE_REQUEST_EXPECT_REQUEST );
     }
 
    MBEDTLS_SSL_DEBUG_MSG( 3, ( "got no certificate request" ) );

     return( SSL_CERTIFICATE_REQUEST_SKIP );
 }
 
     }
     else if( ret == SSL_CERTIFICATE_REQUEST_SKIP )
     {
         ret = 0;
     }
     else
         goto cleanup;
     }
 
     mbedtls_ssl_handshake_set_state( ssl, MBEDTLS_SSL_SERVER_CERTIFICATE );
 
 cleanup:
     }
     else
     {
        MBEDTLS_SSL_DEBUG_MSG( 2, ( "skip write certificate" ) );
     }
 #endif
 
                                          MBEDTLS_SSL_CLIENT_CERTIFICATE_VERIFY );
    }
    else
   {
        MBEDTLS_SSL_DEBUG_MSG( 2, ( "skip write certificate verify" ) );
         mbedtls_ssl_handshake_set_state( ssl, MBEDTLS_SSL_CLIENT_FINISHED );
   }
 
     return( 0 );
 }