     void *empty2 = mbedtls_calloc( 0, 1 );
     void *buffer1 = mbedtls_calloc( 1, 1 );
     void *buffer2 = mbedtls_calloc( 1, 1 );
    uintptr_t old_buffer1;
 
     if( empty1 == NULL && empty2 == NULL )
     {
             mbedtls_printf( "  CALLOC(1): passed\n" );
     }
 
    old_buffer1 = (uintptr_t) buffer1;
     mbedtls_free( buffer1 );
     buffer1 = mbedtls_calloc( 1, 1 );
     if( buffer1 == NULL )
     else
     {
         if( verbose )
            mbedtls_printf( "  CALLOC(1 again): passed (%s address)\n",
                            (uintptr_t) old_buffer1 == (uintptr_t) buffer1 ?
                            "same" : "different" );
     }
 
     if( verbose )