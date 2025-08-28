     else
     {
         ssl->state = MBEDTLS_SSL_SERVER_CHANGE_CIPHER_SPEC;
     }
 
     MBEDTLS_SSL_DEBUG_MSG( 3, ( "%s session has been resumed",
         }
     }
 
    if( ssl->state == MBEDTLS_SSL_SERVER_CHANGE_CIPHER_SPEC )
    {
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

     /*
      * Renegotiation security checks
      */
     size_t sig_alg_len;
 #if defined(MBEDTLS_DEBUG_C)
         unsigned char *sig_alg;
 #endif
 
     MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> parse certificate request" ) );
         return( MBEDTLS_ERR_SSL_DECODE_ERROR );
     }
 
 exit:
     MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= parse certificate request" ) );
 