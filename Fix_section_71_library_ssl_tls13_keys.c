     *dst_len = total_hkdf_lbl_len;
 }
 
 int mbedtls_ssl_tls13_hkdf_expand_label(
                      psa_algorithm_t hash_alg,
                      const unsigned char *secret, size_t secret_len,
                      unsigned char *buf, size_t buf_len )
 {
     unsigned char hkdf_label[ SSL_TLS1_3_KEY_SCHEDULE_MAX_HKDF_LABEL_LEN ];
    size_t hkdf_label_len = 0;
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_status_t abort_status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_derivation_operation_t operation =
        PSA_KEY_DERIVATION_OPERATION_INIT;
 
     if( label_len > MBEDTLS_SSL_TLS1_3_KEY_SCHEDULE_MAX_LABEL_LEN )
     {
                                  hkdf_label,
                                  &hkdf_label_len );
 
    status = psa_key_derivation_setup( &operation, PSA_ALG_HKDF_EXPAND( hash_alg ) );

    if( status != PSA_SUCCESS )
         goto cleanup;

    status = psa_key_derivation_input_bytes( &operation,
                                             PSA_KEY_DERIVATION_INPUT_SECRET,
                                             secret,
                                             secret_len );

    if( status != PSA_SUCCESS )
         goto cleanup;

    status = psa_key_derivation_input_bytes( &operation,
                                             PSA_KEY_DERIVATION_INPUT_INFO,
                                             hkdf_label,
                                             hkdf_label_len );

    if( status != PSA_SUCCESS )
         goto cleanup;

    status = psa_key_derivation_output_bytes( &operation,
                                              buf,
                                              buf_len );

    if( status != PSA_SUCCESS )
         goto cleanup;

cleanup:
    abort_status = psa_key_derivation_abort( &operation );
    status = ( status == PSA_SUCCESS ? abort_status : status );
    mbedtls_platform_zeroize( hkdf_label, hkdf_label_len );
    return( psa_ssl_status_to_mbedtls ( status ) );
 }
 
 /*
                    unsigned char *secret_new )
 {
     int ret = MBEDTLS_ERR_SSL_INTERNAL_ERROR;
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_status_t abort_status = PSA_ERROR_CORRUPTION_DETECTED;
     size_t hlen, ilen;
     unsigned char tmp_secret[ PSA_MAC_MAX_SIZE ] = { 0 };
     unsigned char tmp_input [ MBEDTLS_ECP_MAX_BYTES ] = { 0 };
    psa_key_derivation_operation_t operation =
        PSA_KEY_DERIVATION_OPERATION_INIT;
 
     if( ! PSA_ALG_IS_HASH( hash_alg ) )
         return( MBEDTLS_ERR_SSL_BAD_INPUT_DATA );
             goto cleanup;
     }
 
    ret = 0;

     if( input != NULL )
     {
         memcpy( tmp_input, input, input_len );
         ilen = hlen;
     }
 
    status = psa_key_derivation_setup( &operation,
                                       PSA_ALG_HKDF_EXTRACT( hash_alg ) );
 
    if( status != PSA_SUCCESS )
         goto cleanup;

    status = psa_key_derivation_input_bytes( &operation,
                                             PSA_KEY_DERIVATION_INPUT_SALT,
                                             tmp_secret,
                                             hlen );

    if( status != PSA_SUCCESS )
         goto cleanup;

    status = psa_key_derivation_input_bytes( &operation,
                                             PSA_KEY_DERIVATION_INPUT_SECRET,
                                             tmp_input,
                                             ilen );

    if( status != PSA_SUCCESS )
         goto cleanup;
 
    status = psa_key_derivation_output_bytes( &operation,
                                              secret_new,
                                              PSA_HASH_LENGTH( hash_alg ) );

    if( status != PSA_SUCCESS )
         goto cleanup;

 cleanup:
    abort_status = psa_key_derivation_abort( &operation );
    status = ( status == PSA_SUCCESS ? abort_status : status );
    ret = ( ret == 0 ? psa_ssl_status_to_mbedtls ( status ) : ret );
     mbedtls_platform_zeroize( tmp_secret, sizeof(tmp_secret) );
     mbedtls_platform_zeroize( tmp_input,  sizeof(tmp_input)  );
     return( ret );