         if( ( pk_info = mbedtls_pk_info_from_type( MBEDTLS_PK_RSA ) ) == NULL )
             return( MBEDTLS_ERR_PK_UNKNOWN_PK_ALG );
 
        if( ( ret = mbedtls_pk_setup( ctx, pk_info ) ) != 0 )
             return( ret );
 
         if ( ( ret = pk_get_rsapubkey( &p, p + pem.buflen, mbedtls_pk_rsa( *ctx ) ) ) != 0 )
             mbedtls_pk_free( ctx );