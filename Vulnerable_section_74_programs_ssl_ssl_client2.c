             if( *p == ',' )
                 *p++ = '\0';
 
            if( strcmp( q, "ecdsa_secp256r1_sha256" ) == 0 )
             {
                 sig_alg_list[i++] = MBEDTLS_TLS1_3_SIG_ECDSA_SECP256R1_SHA256;
             }
             {
                 sig_alg_list[i++] = MBEDTLS_TLS1_3_SIG_RSA_PSS_RSAE_SHA512;
             }
            else if( strcmp( q, "rsa_pkcs1_sha256" ) == 0 )
             {
                sig_alg_list[i++] = MBEDTLS_TLS1_3_SIG_RSA_PKCS1_SHA256;
             }
             else
             {
                mbedtls_printf( "unknown signature algorithm %s\n", q );
                mbedtls_printf( "supported signature algorithms: " );
                mbedtls_printf( "ecdsa_secp256r1_sha256 " );
                mbedtls_printf( "ecdsa_secp384r1_sha384 " );
                mbedtls_printf( "ecdsa_secp521r1_sha512 " );
                mbedtls_printf( "rsa_pss_rsae_sha256 " );
                mbedtls_printf( "rsa_pss_rsae_sha384 " );
                mbedtls_printf( "rsa_pss_rsae_sha512 " );
                mbedtls_printf( "rsa_pkcs1_sha256 " );
                mbedtls_printf( "\n" );
                 goto exit;
             }
         }