 #if defined(MBEDTLS_X509_RSASSA_PSS_SUPPORT)
     if( sig_alg == MBEDTLS_PK_RSASSA_PSS )
     {
         rsassa_pss_options.mgf1_hash_id = md_alg;

        rsassa_pss_options.expected_salt_len = PSA_HASH_LENGTH( hash_alg );
         options = (const void*) &rsassa_pss_options;
     }
 #endif /* MBEDTLS_X509_RSASSA_PSS_SUPPORT */
      * from the configuration. */
 #if defined(MBEDTLS_SSL_SRV_C)
     if( ssl->conf->endpoint == MBEDTLS_SSL_IS_SERVER )
    {
#if defined(MBEDTLS_SSL_SERVER_NAME_INDICATION)
        if( ssl->handshake->sni_authmode != MBEDTLS_SSL_VERIFY_UNSET )
            authmode = ssl->handshake->sni_authmode;
        else
#endif
            authmode = ssl->conf->authmode;
    }
 #endif
 
     /*
      */
     if( ssl->session_negotiate->peer_cert == NULL )
     {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "peer has no certificate" ) );
 
 #if defined(MBEDTLS_SSL_SRV_C)
         if( ssl->conf->endpoint == MBEDTLS_SSL_IS_SERVER )
         /* Currently, we don't have any certificate extensions defined.
          * Hence, we are sending an empty extension with length zero.
          */
        MBEDTLS_PUT_UINT16_BE( 0, p, 0 );
         p += 2;
     }
 
 /*
  * STATE HANDLING: Output Certificate Verify
  */

int mbedtls_ssl_tls13_check_sig_alg_cert_key_match( uint16_t sig_alg,
                                                    mbedtls_pk_context *key )
 {
    mbedtls_pk_type_t pk_type = mbedtls_ssl_sig_from_pk( key );
    size_t key_size = mbedtls_pk_get_bitlen( key );
 
    switch( pk_type )
     {
         case MBEDTLS_SSL_SIG_ECDSA:
            switch( key_size )
             {
                 case 256:
                    return(
                        sig_alg == MBEDTLS_TLS1_3_SIG_ECDSA_SECP256R1_SHA256 );

                 case 384:
                    return(
                        sig_alg == MBEDTLS_TLS1_3_SIG_ECDSA_SECP384R1_SHA384 );

                 case 521:
                    return(
                        sig_alg == MBEDTLS_TLS1_3_SIG_ECDSA_SECP521R1_SHA512 );
                 default:
                     break;
             }
             break;
 
         case MBEDTLS_SSL_SIG_RSA:
            switch( sig_alg )
             {
                case MBEDTLS_TLS1_3_SIG_RSA_PSS_RSAE_SHA256:
                    return( key_size <= 3072 );

                case MBEDTLS_TLS1_3_SIG_RSA_PSS_RSAE_SHA384:
                    return( key_size <= 7680 );

                case MBEDTLS_TLS1_3_SIG_RSA_PSS_RSAE_SHA512:
                    return( 1 );

                default:
                    break;
             }
             break;

         default:
             break;
     }

    return( 0 );
}

static int ssl_tls13_select_sig_alg_for_certificate_verify(
                                          mbedtls_ssl_context *ssl,
                                          mbedtls_pk_context *own_key,
                                          uint16_t *algorithm )
{
    uint16_t *sig_alg = ssl->handshake->received_sig_algs;

    *algorithm = MBEDTLS_TLS1_3_SIG_NONE;
    for( ; *sig_alg != MBEDTLS_TLS1_3_SIG_NONE ; sig_alg++ )
    {
        if( mbedtls_ssl_sig_alg_is_offered( ssl, *sig_alg ) &&
            mbedtls_ssl_tls13_sig_alg_for_cert_verify_is_supported( *sig_alg ) &&
            mbedtls_ssl_tls13_check_sig_alg_cert_key_match( *sig_alg, own_key ) )
        {
            MBEDTLS_SSL_DEBUG_MSG( 3,
                                   ( "select_sig_alg_for_certificate_verify:"
                                     "selected signature algorithm %s [%04x]",
                                     mbedtls_ssl_sig_alg_to_str( *sig_alg ),
                                     *sig_alg ) );
            *algorithm = *sig_alg;
            return( 0 );
        }
    }
    MBEDTLS_SSL_DEBUG_MSG( 2,
                           ( "select_sig_alg_for_certificate_verify:"
                             "no suitable signature algorithm found" ) );
     return( -1 );
 }
 
      *    opaque signature<0..2^16-1>;
      *  } CertificateVerify;
      */
    ret = ssl_tls13_select_sig_alg_for_certificate_verify( ssl, own_key,
                                                           &algorithm );
    if( ret != 0 )
     {
         MBEDTLS_SSL_DEBUG_MSG( 1,
                     ( "signature algorithm not in received or offered list." ) );
         return( MBEDTLS_ERR_SSL_HANDSHAKE_FAILURE );
     }
 
    MBEDTLS_SSL_DEBUG_MSG( 2, ( "CertificateVerify with %s",
                                mbedtls_ssl_sig_alg_to_str( algorithm )) );

     if( mbedtls_ssl_tls13_get_pk_type_and_md_alg_from_sig_alg(
                                         algorithm, &pk_type, &md_alg ) != 0 )
     {
     mbedtls_ssl_handshake_params *handshake = ssl->handshake;
 
     /* Get size of the TLS opaque key_exchange field of the KeyShareEntry struct. */
    MBEDTLS_SSL_CHK_BUF_READ_PTR( p, end, 2 );
     uint16_t peerkey_len = MBEDTLS_GET_UINT16_BE( p, 0 );
     p += 2;
 
     /* Check if key size is consistent with given buffer length. */
    MBEDTLS_SSL_CHK_BUF_READ_PTR( p, end, peerkey_len );
 
     /* Store peer's ECDH public key. */
     memcpy( handshake->ecdh_psa_peerkey, p, peerkey_len );