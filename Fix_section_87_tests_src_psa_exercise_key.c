                                        psa_algorithm_t alg )
 {
     psa_key_derivation_operation_t operation = PSA_KEY_DERIVATION_OPERATION_INIT;
    unsigned char input[1] = { 0 };
     unsigned char output[1];
     int ok = 0;
     psa_algorithm_t kdf_alg = PSA_ALG_KEY_AGREEMENT_GET_KDF( alg );
    psa_status_t expected_key_agreement_status = PSA_SUCCESS;
 
     if( usage & PSA_KEY_USAGE_DERIVE )
     {
                             input, sizeof( input ) ) );
         }
 
        if( PSA_ALG_IS_HKDF_EXTRACT( kdf_alg ) )
        {
            PSA_ASSERT( psa_key_derivation_input_bytes(
                &operation, PSA_KEY_DERIVATION_INPUT_SALT,
                input, sizeof( input ) ) );
        }

        /* For HKDF_EXPAND input secret may fail as secret size may not match
           to expected PRK size. In practice it means that key bits must match
           hash length. Otherwise test should fail with INVALID_ARGUMENT. */
        if( PSA_ALG_IS_HKDF_EXPAND( kdf_alg ) )
        {
            psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
            PSA_ASSERT( psa_get_key_attributes( key, &attributes ) );
            size_t key_bits = psa_get_key_bits( &attributes );
            psa_algorithm_t hash_alg = PSA_ALG_HKDF_GET_HASH( kdf_alg );

            if( PSA_BITS_TO_BYTES( key_bits ) != PSA_HASH_LENGTH( hash_alg ) )
                expected_key_agreement_status = PSA_ERROR_INVALID_ARGUMENT;
        }

        TEST_EQUAL( mbedtls_test_psa_key_agreement_with_self( &operation, key ),
                    expected_key_agreement_status );

        if( expected_key_agreement_status != PSA_SUCCESS )
            return( 1 );
 
         if( PSA_ALG_IS_TLS12_PRF( kdf_alg ) ||
             PSA_ALG_IS_TLS12_PSK_TO_MS( kdf_alg ) )
                             &operation, PSA_KEY_DERIVATION_INPUT_LABEL,
                             input, sizeof( input ) ) );
         }
        else if( PSA_ALG_IS_HKDF( kdf_alg ) || PSA_ALG_IS_HKDF_EXPAND( kdf_alg ) )
         {
             PSA_ASSERT( psa_key_derivation_input_bytes(
                             &operation, PSA_KEY_DERIVATION_INPUT_INFO,