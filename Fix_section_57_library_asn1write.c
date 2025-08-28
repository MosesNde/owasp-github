     //
     len = mbedtls_mpi_size( X );
 
    /* DER represents 0 with a sign bit (0=nonnegative) and 7 value bits, not
     * as 0 digits. We need to end up with 020100, not with 0200. */
    if( len == 0 )
        len = 1;

     if( *p < start || (size_t)( *p - start ) < len )
         return( MBEDTLS_ERR_ASN1_BUF_TOO_SMALL );
 