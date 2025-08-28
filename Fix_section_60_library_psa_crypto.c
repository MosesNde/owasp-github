 
 #define ARRAY_LENGTH( array ) ( sizeof( array ) / sizeof( *( array ) ) )
 
#if defined(MBEDTLS_PSA_BUILTIN_ALG_HKDF) ||          \
    defined(MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXTRACT) ||  \
    defined(MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXPAND)
#define BUILTIN_ALG_ANY_HKDF 1
#endif

 /****************************************************************/
 /* Global data, support functions and library management */
 /****************************************************************/
 /* Generators */
 /****************************************************************/
 
#if defined(BUILTIN_ALG_ANY_HKDF) || \
     defined(MBEDTLS_PSA_BUILTIN_ALG_TLS12_PRF) || \
     defined(MBEDTLS_PSA_BUILTIN_ALG_TLS12_PSK_TO_MS)
 #define AT_LEAST_ONE_BUILTIN_KDF
 #endif /* At least one builtin KDF */
 
#if defined(BUILTIN_ALG_ANY_HKDF) || \
     defined(MBEDTLS_PSA_BUILTIN_ALG_TLS12_PRF) || \
     defined(MBEDTLS_PSA_BUILTIN_ALG_TLS12_PSK_TO_MS)
 static psa_status_t psa_key_derivation_start_hmac(
          * nothing to do. */
     }
     else
#if defined(BUILTIN_ALG_ANY_HKDF)
    if( PSA_ALG_IS_ANY_HKDF( kdf_alg ) )
     {
         mbedtls_free( operation->ctx.hkdf.info );
         status = psa_mac_abort( &operation->ctx.hkdf.hmac );
     }
     else
#endif /* BUILTIN_ALG_ANY_HKDF */
 #if defined(MBEDTLS_PSA_BUILTIN_ALG_TLS12_PRF) || \
     defined(MBEDTLS_PSA_BUILTIN_ALG_TLS12_PSK_TO_MS)
     if( PSA_ALG_IS_TLS12_PRF( kdf_alg ) ||
     return( PSA_SUCCESS );
 }
 
#if defined(BUILTIN_ALG_ANY_HKDF)
/* Read some bytes from an HKDF-based operation. */
 static psa_status_t psa_key_derivation_hkdf_read( psa_hkdf_key_derivation_t *hkdf,
                                                  psa_algorithm_t kdf_alg,
                                                   uint8_t *output,
                                                   size_t output_length )
 {
    psa_algorithm_t hash_alg = PSA_ALG_HKDF_GET_HASH( kdf_alg );
     uint8_t hash_length = PSA_HASH_LENGTH( hash_alg );
     size_t hmac_output_length;
     psa_status_t status;
#if defined(MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXTRACT)
    const uint8_t last_block = PSA_ALG_IS_HKDF_EXTRACT( kdf_alg ) ? 0 : 0xff;
#else
    const uint8_t last_block = 0xff;
#endif /* MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXTRACT */

    if( hkdf->state < HKDF_STATE_KEYED ||
        ( !hkdf->info_set
#if defined(MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXTRACT)
         && !PSA_ALG_IS_HKDF_EXTRACT( kdf_alg )
#endif /* MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXTRACT */
    ) )
         return( PSA_ERROR_BAD_STATE );
     hkdf->state = HKDF_STATE_OUTPUT;
 
         hkdf->offset_in_block += n;
         if( output_length == 0 )
             break;
        /* We can't be wanting more output after the last block, otherwise
          * the capacity check in psa_key_derivation_output_bytes() would have
          * prevented this call. It could happen only if the operation
          * object was corrupted or if this function is called directly
          * inside the library. */
        if( hkdf->block_number == last_block )
             return( PSA_ERROR_BAD_STATE );
 
         /* We need a new block */
 
     return( PSA_SUCCESS );
 }
#endif /* BUILTIN_ALG_ANY_HKDF */
 
 #if defined(MBEDTLS_PSA_BUILTIN_ALG_TLS12_PRF) || \
     defined(MBEDTLS_PSA_BUILTIN_ALG_TLS12_PSK_TO_MS)
     }
     operation->capacity -= output_length;
 
#if defined(BUILTIN_ALG_ANY_HKDF)
    if( PSA_ALG_IS_ANY_HKDF( kdf_alg ) )
     {
        status = psa_key_derivation_hkdf_read( &operation->ctx.hkdf, kdf_alg,
                                           output, output_length );
     }
     else
#endif /* BUILTIN_ALG_ANY_HKDF */
 #if defined(MBEDTLS_PSA_BUILTIN_ALG_TLS12_PRF) || \
     defined(MBEDTLS_PSA_BUILTIN_ALG_TLS12_PSK_TO_MS)
     if( PSA_ALG_IS_TLS12_PRF( kdf_alg ) ||
     if( PSA_ALG_IS_HKDF( kdf_alg ) )
         return( 1 );
 #endif
#if defined(MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXTRACT)
    if( PSA_ALG_IS_HKDF_EXTRACT( kdf_alg ) )
        return( 1 );
#endif
#if defined(MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXPAND)
    if( PSA_ALG_IS_HKDF_EXPAND( kdf_alg ) )
        return( 1 );
#endif
 #if defined(MBEDTLS_PSA_BUILTIN_ALG_TLS12_PRF)
     if( PSA_ALG_IS_TLS12_PRF( kdf_alg ) )
         return( 1 );
     {
         return( PSA_ERROR_NOT_SUPPORTED );
     }
#if defined(MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXTRACT)
    if( PSA_ALG_IS_HKDF_EXTRACT( kdf_alg ) )
        operation->capacity = hash_size;
    else
#endif /* MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXTRACT */
        operation->capacity = 255 * hash_size;
     return( PSA_SUCCESS );
 }
 
     return( status );
 }
 
#if defined(BUILTIN_ALG_ANY_HKDF)
 static psa_status_t psa_hkdf_input( psa_hkdf_key_derivation_t *hkdf,
                                    psa_algorithm_t kdf_alg,
                                     psa_key_derivation_step_t step,
                                     const uint8_t *data,
                                     size_t data_length )
 {
    psa_algorithm_t hash_alg = PSA_ALG_HKDF_GET_HASH( kdf_alg );
     psa_status_t status;
     switch( step )
     {
         case PSA_KEY_DERIVATION_INPUT_SALT:
#if defined(MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXPAND)
            if( PSA_ALG_IS_HKDF_EXPAND( kdf_alg ) )
                return( PSA_ERROR_INVALID_ARGUMENT );
#endif /* MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXPAND */
             if( hkdf->state != HKDF_STATE_INIT )
                 return( PSA_ERROR_BAD_STATE );
             else
                 return( PSA_SUCCESS );
             }
         case PSA_KEY_DERIVATION_INPUT_SECRET:
#if defined(MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXPAND)
            if( PSA_ALG_IS_HKDF_EXPAND( kdf_alg ) )
             {
                /* We shouldn't be in different state as HKDF_EXPAND only allows
                 * two inputs: SECRET (this case) and INFO which does not modify
                 * the state. It could happen only if the hkdf
                 * object was corrupted. */
                if( hkdf->state != HKDF_STATE_INIT )
                    return( PSA_ERROR_BAD_STATE );

                /* Allow only input that fits expected prk size */
                if( data_length != PSA_HASH_LENGTH( hash_alg ) )
                    return( PSA_ERROR_INVALID_ARGUMENT );

                memcpy( hkdf->prk, data, data_length );
            }
            else
#endif /* MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXPAND */
            {
                /* HKDF: If no salt was provided, use an empty salt.
                 * HKDF-EXTRACT: salt is mandatory. */
                if( hkdf->state == HKDF_STATE_INIT )
                {
#if defined(MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXTRACT)
                    if( PSA_ALG_IS_HKDF_EXTRACT( kdf_alg ) )
                        return( PSA_ERROR_BAD_STATE );
#endif /* MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXTRACT */
                    status = psa_key_derivation_start_hmac( &hkdf->hmac,
                                                            hash_alg,
                                                            NULL, 0 );
                    if( status != PSA_SUCCESS )
                        return( status );
                    hkdf->state = HKDF_STATE_STARTED;
                }
                if( hkdf->state != HKDF_STATE_STARTED )
                    return( PSA_ERROR_BAD_STATE );
                status = psa_mac_update( &hkdf->hmac,
                                        data, data_length );
                if( status != PSA_SUCCESS )
                    return( status );
                status = psa_mac_sign_finish( &hkdf->hmac,
                                            hkdf->prk,
                                            sizeof( hkdf->prk ),
                                            &data_length );
                 if( status != PSA_SUCCESS )
                     return( status );
             }

             hkdf->state = HKDF_STATE_KEYED;
            hkdf->block_number = 0;
#if defined(MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXTRACT)
            if( PSA_ALG_IS_HKDF_EXTRACT( kdf_alg ) )
            {
                /* The only block of output is the PRK. */
                memcpy( hkdf->output_block, hkdf->prk, PSA_HASH_LENGTH( hash_alg ) );
                hkdf->offset_in_block = 0;
            }
            else
#endif /* MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXTRACT */
            {
                /* Block 0 is empty, and the next block will be
                 * generated by psa_key_derivation_hkdf_read(). */
                hkdf->offset_in_block = PSA_HASH_LENGTH( hash_alg );
            }

             return( PSA_SUCCESS );
         case PSA_KEY_DERIVATION_INPUT_INFO:
#if defined(MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXTRACT)
            if( PSA_ALG_IS_HKDF_EXTRACT( kdf_alg ) )
                return( PSA_ERROR_INVALID_ARGUMENT );
#endif /* MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXTRACT */
#if defined(MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXPAND)
            if( PSA_ALG_IS_HKDF_EXPAND( kdf_alg ) &&
                hkdf->state == HKDF_STATE_INIT )
                return( PSA_ERROR_BAD_STATE );
#endif /* MBEDTLS_PSA_BUILTIN_ALG_HKDF_EXTRACT */
             if( hkdf->state == HKDF_STATE_OUTPUT )
                 return( PSA_ERROR_BAD_STATE );
             if( hkdf->info_set )
             return( PSA_ERROR_INVALID_ARGUMENT );
     }
 }
#endif /* BUILTIN_ALG_ANY_HKDF */
 
 #if defined(MBEDTLS_PSA_BUILTIN_ALG_TLS12_PRF) || \
     defined(MBEDTLS_PSA_BUILTIN_ALG_TLS12_PSK_TO_MS)
     if( status != PSA_SUCCESS )
         goto exit;
 
#if defined(BUILTIN_ALG_ANY_HKDF)
    if( PSA_ALG_IS_ANY_HKDF( kdf_alg ) )
     {
        status = psa_hkdf_input( &operation->ctx.hkdf, kdf_alg,
                                  step, data, data_length );
     }
     else
#endif /* BUILTIN_ALG_ANY_HKDF */
 #if defined(MBEDTLS_PSA_BUILTIN_ALG_TLS12_PRF)
     if( PSA_ALG_IS_TLS12_PRF( kdf_alg ) )
     {