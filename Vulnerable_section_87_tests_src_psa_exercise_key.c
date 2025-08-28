                                        psa_algorithm_t alg )
 {
     psa_key_derivation_operation_t operation = PSA_KEY_DERIVATION_OPERATION_INIT;
    unsigned char input[1];
     unsigned char output[1];
     int ok = 0;
     psa_algorithm_t kdf_alg = PSA_ALG_KEY_AGREEMENT_GET_KDF( alg );
 
     if( usage & PSA_KEY_USAGE_DERIVE )
     {
                             input, sizeof( input ) ) );
         }
 
        PSA_ASSERT( mbedtls_test_psa_key_agreement_with_self( &operation, key ) );
 
         if( PSA_ALG_IS_TLS12_PRF( kdf_alg ) ||
             PSA_ALG_IS_TLS12_PSK_TO_MS( kdf_alg ) )
                             &operation, PSA_KEY_DERIVATION_INPUT_LABEL,
                             input, sizeof( input ) ) );
         }
        else if( PSA_ALG_IS_HKDF( kdf_alg ) )
         {
             PSA_ASSERT( psa_key_derivation_input_bytes(
                             &operation, PSA_KEY_DERIVATION_INPUT_INFO,