     *dst_len = total_hkdf_lbl_len;
 }
 
MBEDTLS_STATIC_TESTABLE
psa_status_t mbedtls_psa_hkdf_extract( psa_algorithm_t hash_alg,
                                       const unsigned char *salt, size_t salt_len,
                                       const unsigned char *ikm, size_t ikm_len,
                                       unsigned char *prk, size_t prk_size,
                                       size_t *prk_len )
{
    unsigned char null_salt[PSA_MAC_MAX_SIZE] = { '\0' };
    mbedtls_svc_key_id_t key = MBEDTLS_SVC_KEY_ID_INIT;
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_status_t destroy_status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_algorithm_t alg = PSA_ALG_HMAC( hash_alg );

    if( salt == NULL || salt_len == 0 )
    {
        size_t hash_len;

        if( salt_len != 0 )
        {
            return( PSA_ERROR_INVALID_ARGUMENT );
        }

        hash_len = PSA_HASH_LENGTH( alg );

        if( hash_len == 0 )
        {
            return( PSA_ERROR_INVALID_ARGUMENT );
        }

        /* salt_len <= sizeof( salt ) because
           PSA_HASH_LENGTH( alg ) <= PSA_MAC_MAX_SIZE. */
        salt = null_salt;
        salt_len = hash_len;
    }

    psa_set_key_usage_flags( &attributes, PSA_KEY_USAGE_SIGN_MESSAGE );
    psa_set_key_algorithm( &attributes, alg );
    psa_set_key_type( &attributes, PSA_KEY_TYPE_HMAC );

    status = psa_import_key( &attributes, salt, salt_len, &key );
    if( status != PSA_SUCCESS )
    {
        goto cleanup;
    }

    status = psa_mac_compute( key, alg, ikm, ikm_len, prk, prk_size, prk_len );

cleanup:
    destroy_status = psa_destroy_key( key );

    return( ( status == PSA_SUCCESS ) ? destroy_status : status );
}

MBEDTLS_STATIC_TESTABLE
psa_status_t mbedtls_psa_hkdf_expand( psa_algorithm_t hash_alg,
                                      const unsigned char *prk, size_t prk_len,
                                      const unsigned char *info, size_t info_len,
                                      unsigned char *okm, size_t okm_len )
{
    size_t hash_len;
    size_t where = 0;
    size_t n;
    size_t t_len = 0;
    size_t i;
    mbedtls_svc_key_id_t key = MBEDTLS_SVC_KEY_ID_INIT;
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
    psa_mac_operation_t operation = PSA_MAC_OPERATION_INIT;
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_status_t destroy_status = PSA_ERROR_CORRUPTION_DETECTED;
    unsigned char t[PSA_MAC_MAX_SIZE];
    psa_algorithm_t alg = PSA_ALG_HMAC( hash_alg );

    if( okm == NULL )
    {
        return( PSA_ERROR_INVALID_ARGUMENT );
    }

    hash_len = PSA_HASH_LENGTH( alg );

    if( prk_len < hash_len || hash_len == 0 )
    {
        return( PSA_ERROR_INVALID_ARGUMENT );
    }

    if( info == NULL )
    {
        info = (const unsigned char *) "";
        info_len = 0;
    }

    n = okm_len / hash_len;

    if( okm_len % hash_len != 0 )
    {
        n++;
    }

    /*
     * Per RFC 5869 Section 2.3, okm_len must not exceed
     * 255 times the hash length
     */
    if( n > 255 )
    {
        return( PSA_ERROR_INVALID_ARGUMENT );
    }

    psa_set_key_usage_flags( &attributes, PSA_KEY_USAGE_SIGN_MESSAGE );
    psa_set_key_algorithm( &attributes, alg );
    psa_set_key_type( &attributes, PSA_KEY_TYPE_HMAC );

    status = psa_import_key( &attributes, prk, prk_len, &key );
    if( status != PSA_SUCCESS )
    {
        goto cleanup;
    }

    memset( t, 0, hash_len );

    /*
     * Compute T = T(1) | T(2) | T(3) | ... | T(N)
     * Where T(N) is defined in RFC 5869 Section 2.3
     */
    for( i = 1; i <= n; i++ )
    {
        size_t num_to_copy;
        unsigned char c = i & 0xff;
        size_t len;

        status = psa_mac_sign_setup( &operation, key, alg );
        if( status != PSA_SUCCESS )
        {
            goto cleanup;
        }

        status = psa_mac_update( &operation, t, t_len );
        if( status != PSA_SUCCESS )
        {
            goto cleanup;
        }

        status = psa_mac_update( &operation, info, info_len );
        if( status != PSA_SUCCESS )
        {
            goto cleanup;
        }

        /* The constant concatenated to the end of each T(n) is a single octet. */
        status = psa_mac_update( &operation, &c, 1 );
        if( status != PSA_SUCCESS )
        {
            goto cleanup;
        }

        status = psa_mac_sign_finish( &operation, t, PSA_MAC_MAX_SIZE, &len );
        if( status != PSA_SUCCESS )
        {
            goto cleanup;
        }

        num_to_copy = i != n ? hash_len : okm_len - where;
        memcpy( okm + where, t, num_to_copy );
        where += hash_len;
        t_len = hash_len;
    }

cleanup:
    if( status != PSA_SUCCESS )
        psa_mac_abort( &operation );
    destroy_status = psa_destroy_key( key );

    mbedtls_platform_zeroize( t, sizeof( t ) );

    return( ( status == PSA_SUCCESS ) ? destroy_status : status );
}

 int mbedtls_ssl_tls13_hkdf_expand_label(
                      psa_algorithm_t hash_alg,
                      const unsigned char *secret, size_t secret_len,
                      unsigned char *buf, size_t buf_len )
 {
     unsigned char hkdf_label[ SSL_TLS1_3_KEY_SCHEDULE_MAX_HKDF_LABEL_LEN ];
    size_t hkdf_label_len;
 
     if( label_len > MBEDTLS_SSL_TLS1_3_KEY_SCHEDULE_MAX_LABEL_LEN )
     {
                                  hkdf_label,
                                  &hkdf_label_len );
 
    return( psa_ssl_status_to_mbedtls(
                mbedtls_psa_hkdf_expand( hash_alg,
                                         secret, secret_len,
                                         hkdf_label, hkdf_label_len,
                                         buf, buf_len ) ) );
 }
 
 /*
                    unsigned char *secret_new )
 {
     int ret = MBEDTLS_ERR_SSL_INTERNAL_ERROR;
     size_t hlen, ilen;
     unsigned char tmp_secret[ PSA_MAC_MAX_SIZE ] = { 0 };
     unsigned char tmp_input [ MBEDTLS_ECP_MAX_BYTES ] = { 0 };
    size_t secret_len;
 
     if( ! PSA_ALG_IS_HASH( hash_alg ) )
         return( MBEDTLS_ERR_SSL_BAD_INPUT_DATA );
             goto cleanup;
     }
 
     if( input != NULL )
     {
         memcpy( tmp_input, input, input_len );
         ilen = hlen;
     }
 
    /* HKDF-Extract takes a salt and input key material.
     * The salt is the old secret, and the input key material
     * is the input secret (PSK / ECDHE). */
    ret = psa_ssl_status_to_mbedtls(
            mbedtls_psa_hkdf_extract( hash_alg,
                                      tmp_secret, hlen,
                                      tmp_input, ilen,
                                      secret_new, hlen, &secret_len ) );
 
 cleanup:
 
     mbedtls_platform_zeroize( tmp_secret, sizeof(tmp_secret) );
     mbedtls_platform_zeroize( tmp_input,  sizeof(tmp_input)  );
     return( ret );