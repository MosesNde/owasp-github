     else
     {
         ssl->state = MBEDTLS_SSL_SERVER_CHANGE_CIPHER_SPEC;

        if( ( ret = mbedtls_ssl_derive_keys( ssl ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_derive_keys", ret );
            mbedtls_ssl_send_alert_message(
                ssl,
                MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                MBEDTLS_SSL_ALERT_MSG_INTERNAL_ERROR );
            return( ret );
        }
     }
 
     MBEDTLS_SSL_DEBUG_MSG( 3, ( "%s session has been resumed",
         }
     }
 
     /*
      * Renegotiation security checks
      */
     size_t sig_alg_len;
 #if defined(MBEDTLS_DEBUG_C)
         unsigned char *sig_alg;
        unsigned char *dn;
 #endif
 
     MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> parse certificate request" ) );
         return( MBEDTLS_ERR_SSL_DECODE_ERROR );
     }
 
#if defined(MBEDTLS_DEBUG_C)
    dn = buf + mbedtls_ssl_hs_hdr_len( ssl ) + 3 + n - dn_len;
    for( size_t i = 0, dni_len = 0; i < dn_len; i += 2 + dni_len )
    {
        unsigned char *p = dn + i + 2;
        mbedtls_x509_name name;
        mbedtls_x509_name *name_cur, *name_prv;
        size_t asn1_len;
        char s[MBEDTLS_X509_MAX_DN_NAME_SIZE];
        memset( &name, 0, sizeof( name ) );
        dni_len = MBEDTLS_GET_UINT16_BE( dn + i, 0 );
        if( dni_len > dn_len - i - 2 ||
            mbedtls_asn1_get_tag( &p, p + dni_len, &asn1_len,
              MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) != 0 ||
            mbedtls_x509_get_name( &p, p + asn1_len, &name ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad certificate request message" ) );
            mbedtls_ssl_send_alert_message(
                ssl,
                MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                MBEDTLS_SSL_ALERT_MSG_DECODE_ERROR );
            return( MBEDTLS_ERR_SSL_DECODE_ERROR );
        }
        MBEDTLS_SSL_DEBUG_MSG( 3,
            ( "DN hint: %.*s",
              mbedtls_x509_dn_gets( s, sizeof(s), &name ), s ) );
        name_cur = name.next;
        while( name_cur != NULL )
        {
            name_prv = name_cur;
            name_cur = name_cur->next;
            mbedtls_platform_zeroize( name_prv, sizeof( mbedtls_x509_name ) );
            mbedtls_free( name_prv );
        }
    }
#endif

 exit:
     MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= parse certificate request" ) );
 