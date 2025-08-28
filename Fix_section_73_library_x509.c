     return( 0 );
 }
 
/*
 * Convert md type to string
 */
static inline const char* md_type_to_string( mbedtls_md_type_t md_alg )
{
    switch( md_alg )
    {
#if defined(MBEDTLS_MD5_C)
    case MBEDTLS_MD_MD5:
        return( "MD5" );
#endif
#if defined(MBEDTLS_SHA1_C)
    case MBEDTLS_MD_SHA1:
        return( "SHA1" );
#endif
#if defined(MBEDTLS_SHA224_C)
    case MBEDTLS_MD_SHA224:
        return( "SHA224" );
#endif
#if defined(MBEDTLS_SHA256_C)
    case MBEDTLS_MD_SHA256:
        return( "SHA256" );
#endif
#if defined(MBEDTLS_SHA384_C)
    case MBEDTLS_MD_SHA384:
        return( "SHA384" );
#endif
#if defined(MBEDTLS_SHA512_C)
    case MBEDTLS_MD_SHA512:
        return( "SHA512" );
#endif
#if defined(MBEDTLS_RIPEMD160_C)
    case MBEDTLS_MD_RIPEMD160:
        return( "RIPEMD160" );
#endif
    case MBEDTLS_MD_NONE:
        return( NULL );
    default:
        return( NULL );
    }
}

 #if defined(MBEDTLS_X509_RSASSA_PSS_SUPPORT)
 /*
  * HashAlgorithm ::= AlgorithmIdentifier
 int mbedtls_x509_dn_gets( char *buf, size_t size, const mbedtls_x509_name *dn )
 {
     int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    size_t i, j, n;
     unsigned char c, merge = 0;
     const mbedtls_x509_name *name;
     const char *short_name = NULL;
             ret = mbedtls_snprintf( p, n, "\?\?=" );
         MBEDTLS_X509_SAFE_SNPRINTF;
 
        for( i = 0, j = 0; i < name->val.len; i++, j++ )
         {
            if( j >= sizeof( s ) - 1 )
                return( MBEDTLS_ERR_X509_BUFFER_TOO_SMALL );
 
             c = name->val.p[i];
            // Special characters requiring escaping, RFC 1779
            if( c && strchr( ",=+<>#;\"\\", c ) )
            {
                if( j + 1 >= sizeof( s ) - 1 )
                    return( MBEDTLS_ERR_X509_BUFFER_TOO_SMALL );
                s[j++] = '\\';
            }
             if( c < 32 || c >= 127 )
                 s[j] = '?';
            else s[j] = c;
         }
        s[j] = '\0';
         ret = mbedtls_snprintf( p, n, "%s", s );
         MBEDTLS_X509_SAFE_SNPRINTF;
 
     if( pk_alg == MBEDTLS_PK_RSASSA_PSS )
     {
         const mbedtls_pk_rsassa_pss_options *pss_opts;
 
         pss_opts = (const mbedtls_pk_rsassa_pss_options *) sig_opts;
 
        const char *name = md_type_to_string( md_alg );
        const char *mgf_name = md_type_to_string( pss_opts->mgf1_hash_id );
 
         ret = mbedtls_snprintf( p, n, " (%s, MGF1-%s, 0x%02X)",
                              name ? name : "???",
                              mgf_name ? mgf_name : "???",
                               (unsigned int) pss_opts->expected_salt_len );
         MBEDTLS_X509_SAFE_SNPRINTF;
     }