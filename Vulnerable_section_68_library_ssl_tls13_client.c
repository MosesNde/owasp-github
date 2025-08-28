 
 #if defined(MBEDTLS_SSL_ALPN)
 static int ssl_tls13_parse_alpn_ext( mbedtls_ssl_context *ssl,
                               const unsigned char *buf, size_t len )
 {
    size_t list_len, name_len;
     const unsigned char *p = buf;
     const unsigned char *end = buf + len;
 
     /* If we didn't send it, the server shouldn't send it */
     if( ssl->conf->alpn_list == NULL )
      * the "ProtocolNameList" MUST contain exactly one "ProtocolName"
      */
 
    /* Min length is 2 ( list_len ) + 1 ( name_len ) + 1 ( name ) */
    MBEDTLS_SSL_CHK_BUF_READ_PTR( p, end, 4 );

    list_len = MBEDTLS_GET_UINT16_BE( p, 0 );
     p += 2;
    MBEDTLS_SSL_CHK_BUF_READ_PTR( p, end, list_len );
 
    name_len = *p++;
    MBEDTLS_SSL_CHK_BUF_READ_PTR( p, end, list_len - 1 );
 
     /* Check that the server chosen protocol was in our list and save it */
    for ( const char **alpn = ssl->conf->alpn_list; *alpn != NULL; alpn++ )
     {
        if( name_len == strlen( *alpn ) &&
            memcmp( buf + 3, *alpn, name_len ) == 0 )
         {
             ssl->alpn_chosen = *alpn;
             return( 0 );
      * - cipher_suite               2 bytes
      * - legacy_compression_method  1 byte
      */
      p += legacy_session_id_echo_len + 4;
 
     /* Case of no extension */
 }
 
 /* Returns a negative value on failure, and otherwise
 * - SSL_SERVER_HELLO_COORDINATE_HELLO or
 * - SSL_SERVER_HELLO_COORDINATE_HRR
  * to indicate which message is expected and to be parsed next.
  */
#define SSL_SERVER_HELLO_COORDINATE_HELLO 0
#define SSL_SERVER_HELLO_COORDINATE_HRR 1
 static int ssl_server_hello_is_hrr( mbedtls_ssl_context *ssl,
                                     const unsigned char *buf,
                                     const unsigned char *end )
     if( memcmp( buf + 2, mbedtls_ssl_tls13_hello_retry_request_magic,
                 sizeof( mbedtls_ssl_tls13_hello_retry_request_magic ) ) == 0 )
     {
        return( SSL_SERVER_HELLO_COORDINATE_HRR );
     }
 
    return( SSL_SERVER_HELLO_COORDINATE_HELLO );
 }
 
/* Fetch and preprocess
  * Returns a negative value on failure, and otherwise
 * - SSL_SERVER_HELLO_COORDINATE_HELLO or
 * - SSL_SERVER_HELLO_COORDINATE_HRR or
 * - SSL_SERVER_HELLO_COORDINATE_TLS1_2
  */
#define SSL_SERVER_HELLO_COORDINATE_TLS1_2 2
static int ssl_tls13_server_hello_coordinate( mbedtls_ssl_context *ssl,
                                              unsigned char **buf,
                                              size_t *buf_len )
 {
     int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    const unsigned char *end;

    MBEDTLS_SSL_PROC_CHK( mbedtls_ssl_tls13_fetch_handshake_msg( ssl,
                                             MBEDTLS_SSL_HS_SERVER_HELLO,
                                             buf, buf_len ) );
    end = *buf + *buf_len;
 
     MBEDTLS_SSL_PROC_CHK_NEG( ssl_tls13_is_supported_versions_ext_present(
                                  ssl, *buf, end ) );
     if( ret == 0 )
     {
         MBEDTLS_SSL_PROC_CHK_NEG(
            ssl_tls13_is_downgrade_negotiation( ssl, *buf, end ) );
 
         /* If the server is negotiating TLS 1.2 or below and:
          * . we did not propose TLS 1.2 or
          * . the server responded it is TLS 1.3 capable but negotiating a lower
          *   version of the protocol and thus we are under downgrade attack
          * abort the handshake with an "illegal parameter" alert.
          */
        if( ssl->handshake->min_tls_version > MBEDTLS_SSL_VERSION_TLS1_2 || ret )
         {
             MBEDTLS_SSL_PEND_FATAL_ALERT( MBEDTLS_SSL_ALERT_MSG_ILLEGAL_PARAMETER,
                                           MBEDTLS_ERR_SSL_ILLEGAL_PARAMETER );
         ssl->keep_current_message = 1;
         ssl->tls_version = MBEDTLS_SSL_VERSION_TLS1_2;
         mbedtls_ssl_add_hs_msg_to_checksum( ssl, MBEDTLS_SSL_HS_SERVER_HELLO,
                                            *buf, *buf_len );
 
         if( mbedtls_ssl_conf_tls13_some_ephemeral_enabled( ssl ) )
         {
                 return( ret );
         }
 
        return( SSL_SERVER_HELLO_COORDINATE_TLS1_2 );
     }
 
    ret = ssl_server_hello_is_hrr( ssl, *buf, end );
     switch( ret )
     {
        case SSL_SERVER_HELLO_COORDINATE_HELLO:
             MBEDTLS_SSL_DEBUG_MSG( 2, ( "received ServerHello message" ) );
             break;
        case SSL_SERVER_HELLO_COORDINATE_HRR:
             MBEDTLS_SSL_DEBUG_MSG( 2, ( "received HelloRetryRequest message" ) );
              /* If a client receives a second
               * HelloRetryRequest in the same connection (i.e., where the ClientHello
               * was itself in response to a HelloRetryRequest), it MUST abort the
               * handshake with an "unexpected_message" alert.
               */
            if( ssl->handshake->hello_retry_request_count > 0 )
             {
                 MBEDTLS_SSL_DEBUG_MSG( 1, ( "Multiple HRRs received" ) );
                 MBEDTLS_SSL_PEND_FATAL_ALERT( MBEDTLS_SSL_ALERT_MSG_UNEXPECTED_MESSAGE,
                 return( MBEDTLS_ERR_SSL_ILLEGAL_PARAMETER );
             }
 
            ssl->handshake->hello_retry_request_count++;
 
             break;
     }
     MBEDTLS_SSL_DEBUG_MSG( 1, ( "Switch to handshake keys for inbound traffic" ) );
     ssl->session_in = ssl->session_negotiate;
 
    /*
     * State machine update
     */
    mbedtls_ssl_handshake_set_state( ssl, MBEDTLS_SSL_ENCRYPTED_EXTENSIONS );

 cleanup:
     if( ret != 0 )
     {
 {
     int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
 
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

     mbedtls_ssl_session_reset_msg_layer( ssl, 0 );
 
     /*
 
     MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> %s", __func__ ) );
 
    /* Coordination step
     * - Fetch record
     * - Make sure it's either a ServerHello or a HRR.
     * - Switch processing routine in case of HRR
     */
    ssl->handshake->extensions_present = MBEDTLS_SSL_EXT_NONE;
 
    ret = ssl_tls13_server_hello_coordinate( ssl, &buf, &buf_len );
     if( ret < 0 )
         goto cleanup;
     else
        is_hrr = ( ret == SSL_SERVER_HELLO_COORDINATE_HRR );
 
    if( ret == SSL_SERVER_HELLO_COORDINATE_TLS1_2 )
     {
         ret = 0;
         goto cleanup;
                                         buf, buf_len );
 
     if( is_hrr )
         MBEDTLS_SSL_PROC_CHK( ssl_tls13_postprocess_hrr( ssl ) );
     else
         MBEDTLS_SSL_PROC_CHK( ssl_tls13_postprocess_server_hello( ssl ) );
 
 cleanup:
     MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= %s ( %s )", __func__,
 
 /*
  *
 * EncryptedExtensions message
  *
  * The EncryptedExtensions message contains any extensions which
  * should be protected, i.e., any which are not needed to establish
  * the cryptographic context.
  */
 
/*
 * Overview
 */

/* Main entry point; orchestrates the other functions */
static int ssl_tls13_process_encrypted_extensions( mbedtls_ssl_context *ssl );

static int ssl_tls13_parse_encrypted_extensions( mbedtls_ssl_context *ssl,
                                                 const unsigned char *buf,
                                                 const unsigned char *end );
static int ssl_tls13_postprocess_encrypted_extensions( mbedtls_ssl_context *ssl );

/*
 * Handler for  MBEDTLS_SSL_ENCRYPTED_EXTENSIONS
 */
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

    MBEDTLS_SSL_PROC_CHK( ssl_tls13_postprocess_encrypted_extensions( ssl ) );

cleanup:

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= parse encrypted extensions" ) );
    return( ret );

}

 /* Parse EncryptedExtensions message
  * struct {
  *     Extension extensions<0..2^16-1>;
     p += 2;
 
     MBEDTLS_SSL_DEBUG_BUF( 3, "encrypted extensions", p, extensions_len );
    extensions_end = p + extensions_len;
     MBEDTLS_SSL_CHK_BUF_READ_PTR( p, end, extensions_len );
 
     while( p < extensions_end )
     {
     return( ret );
 }
 
static int ssl_tls13_postprocess_encrypted_extensions( mbedtls_ssl_context *ssl )
 {
 #if defined(MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED)
     if( mbedtls_ssl_tls13_some_psk_enabled( ssl ) )
         mbedtls_ssl_handshake_set_state( ssl, MBEDTLS_SSL_SERVER_FINISHED );
     ((void) ssl);
     mbedtls_ssl_handshake_set_state( ssl, MBEDTLS_SSL_SERVER_FINISHED );
 #endif
    return( 0 );
 }
 
 #if defined(MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED)
 /*
 *
  * STATE HANDLING: CertificateRequest
  *
  */
     if( ( ssl->in_msgtype == MBEDTLS_SSL_MSG_HANDSHAKE ) &&
         ( ssl->in_msg[0] == MBEDTLS_SSL_HS_CERTIFICATE_REQUEST ) )
     {
         return( SSL_CERTIFICATE_REQUEST_EXPECT_REQUEST );
     }
 
     return( SSL_CERTIFICATE_REQUEST_SKIP );
 }
 
     }
     else if( ret == SSL_CERTIFICATE_REQUEST_SKIP )
     {
        MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= skip parse certificate request" ) );
         ret = 0;
     }
     else
         goto cleanup;
     }
 
    MBEDTLS_SSL_DEBUG_MSG( 3, ( "got %s certificate request",
                                ssl->handshake->client_auth ? "a" : "no" ) );

     mbedtls_ssl_handshake_set_state( ssl, MBEDTLS_SSL_SERVER_CERTIFICATE );
 
 cleanup:
     }
     else
     {
        MBEDTLS_SSL_DEBUG_MSG( 2, ( "No certificate message to send." ) );
     }
 #endif
 
                                          MBEDTLS_SSL_CLIENT_CERTIFICATE_VERIFY );
    }
    else
         mbedtls_ssl_handshake_set_state( ssl, MBEDTLS_SSL_CLIENT_FINISHED );
 
     return( 0 );
 }