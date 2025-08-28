     void *empty2 = mbedtls_calloc( 0, 1 );
     void *buffer1 = mbedtls_calloc( 1, 1 );
     void *buffer2 = mbedtls_calloc( 1, 1 );
 
     if( empty1 == NULL && empty2 == NULL )
     {
             mbedtls_printf( "  CALLOC(1): passed\n" );
     }
 
     mbedtls_free( buffer1 );
     buffer1 = mbedtls_calloc( 1, 1 );
     if( buffer1 == NULL )
     else
     {
         if( verbose )
            mbedtls_printf( "  CALLOC(1 again): passed\n" );
     }
 
     if( verbose )