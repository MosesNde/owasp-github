     //
     len = mbedtls_mpi_size( X );
 
     if( *p < start || (size_t)( *p - start ) < len )
         return( MBEDTLS_ERR_ASN1_BUF_TOO_SMALL );
 