             if( *p == ',' )
                 *p++ = '\0';
 
            if( strcmp( q, "rsa_pkcs1_sha256" ) == 0 )
            {
                sig_alg_list[i++] = MBEDTLS_TLS1_3_SIG_RSA_PKCS1_SHA256;
            }
            else if( strcmp( q, "rsa_pkcs1_sha384" ) == 0 )
            {
                sig_alg_list[i++] = MBEDTLS_TLS1_3_SIG_RSA_PKCS1_SHA384;
            }
            else if( strcmp( q, "rsa_pkcs1_sha512" ) == 0 )
            {
                sig_alg_list[i++] = MBEDTLS_TLS1_3_SIG_RSA_PKCS1_SHA512;
            }
            else if( strcmp( q, "ecdsa_secp256r1_sha256" ) == 0 )
             {
                 sig_alg_list[i++] = MBEDTLS_TLS1_3_SIG_ECDSA_SECP256R1_SHA256;
             }
             {
                 sig_alg_list[i++] = MBEDTLS_TLS1_3_SIG_RSA_PSS_RSAE_SHA512;
             }
            else if( strcmp( q, "ed25519" ) == 0 )
             {
                sig_alg_list[i++] = MBEDTLS_TLS1_3_SIG_ED25519;
            }
            else if( strcmp( q, "ed448" ) == 0 )
            {
                sig_alg_list[i++] = MBEDTLS_TLS1_3_SIG_ED448;
            }
            else if( strcmp( q, "rsa_pss_pss_sha256" ) == 0 )
            {
                sig_alg_list[i++] = MBEDTLS_TLS1_3_SIG_RSA_PSS_PSS_SHA256;
            }
            else if( strcmp( q, "rsa_pss_pss_sha384" ) == 0 )
            {
                sig_alg_list[i++] = MBEDTLS_TLS1_3_SIG_RSA_PSS_PSS_SHA384;
            }
            else if( strcmp( q, "rsa_pss_pss_sha512" ) == 0 )
            {
                sig_alg_list[i++] = MBEDTLS_TLS1_3_SIG_RSA_PSS_PSS_SHA512;
            }
            else if( strcmp( q, "rsa_pkcs1_sha1" ) == 0 )
            {
                sig_alg_list[i++] = MBEDTLS_TLS1_3_SIG_RSA_PKCS1_SHA1;
            }
            else if( strcmp( q, "ecdsa_sha1" ) == 0 )
            {
                sig_alg_list[i++] = MBEDTLS_TLS1_3_SIG_ECDSA_SHA1;
             }
             else
             {
                ret = -1;
                mbedtls_printf( "unknown signature algorithm \"%s\"\n", q );
                mbedtls_print_supported_sig_algs();
                 goto exit;
             }
         }