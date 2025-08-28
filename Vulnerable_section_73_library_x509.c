     return( 0 );
 }
 
 #if defined(MBEDTLS_X509_RSASSA_PSS_SUPPORT)
 /*
  * HashAlgorithm ::= AlgorithmIdentifier
 int mbedtls_x509_dn_gets( char *buf, size_t size, const mbedtls_x509_name *dn )
 {
     int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    size_t i, n;
     unsigned char c, merge = 0;
     const mbedtls_x509_name *name;
     const char *short_name = NULL;
             ret = mbedtls_snprintf( p, n, "\?\?=" );
         MBEDTLS_X509_SAFE_SNPRINTF;
 
        for( i = 0; i < name->val.len; i++ )
         {
            if( i >= sizeof( s ) - 1 )
                break;
 
             c = name->val.p[i];
             if( c < 32 || c >= 127 )
                 s[i] = '?';
            else s[i] = c;
         }
        s[i] = '\0';
         ret = mbedtls_snprintf( p, n, "%s", s );
         MBEDTLS_X509_SAFE_SNPRINTF;
 
     if( pk_alg == MBEDTLS_PK_RSASSA_PSS )
     {
         const mbedtls_pk_rsassa_pss_options *pss_opts;
        const mbedtls_md_info_t *md_info, *mgf_md_info;
 
         pss_opts = (const mbedtls_pk_rsassa_pss_options *) sig_opts;
 
        md_info = mbedtls_md_info_from_type( md_alg );
        mgf_md_info = mbedtls_md_info_from_type( pss_opts->mgf1_hash_id );
 
         ret = mbedtls_snprintf( p, n, " (%s, MGF1-%s, 0x%02X)",
                              md_info ? mbedtls_md_get_name( md_info ) : "???",
                              mgf_md_info ? mbedtls_md_get_name( mgf_md_info ) : "???",
                               (unsigned int) pss_opts->expected_salt_len );
         MBEDTLS_X509_SAFE_SNPRINTF;
     }