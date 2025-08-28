 #endif
 
     if( session_serialized != NULL )
         mbedtls_platform_zeroize( session_serialized, session_serialized_len );
 
     return( ret );
 }