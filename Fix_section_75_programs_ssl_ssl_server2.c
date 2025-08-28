 #define DFL_CID_VALUE_RENEGO    NULL
 #define DFL_AUTH_MODE           -1
 #define DFL_CERT_REQ_CA_LIST    MBEDTLS_SSL_CERT_REQ_CA_LIST_ENABLED
#define DFL_CERT_REQ_DN_HINT    0
 #define DFL_MFL_CODE            MBEDTLS_SSL_MAX_FRAG_LEN_NONE
 #define DFL_TRUNC_HMAC          -1
 #define DFL_TICKETS             MBEDTLS_SSL_SESSION_TICKETS_ENABLED
     "                        options: none, optional, required\n" \
     "    cert_req_ca_list=%%d default: 1 (send ca list)\n"  \
     "                        options: 1 (send ca list), 0 (don't send)\n" \
    "                                 2 (send conf dn hint), 3 (send hs dn hint)\n" \
     USAGE_IO                                                \
     USAGE_KEY_OPAQUE                                        \
     "\n"                                                    \
     int allow_sha1;             /* flag for SHA-1 support                   */
     int auth_mode;              /* verify mode for connection               */
     int cert_req_ca_list;       /* should we send the CA list?              */
    int cert_req_dn_hint;       /* mode to set DN hints for CA list to send */
     unsigned char mfl_code;     /* code for maximum fragment length         */
     int trunc_hmac;             /* accept truncated hmac?                   */
     int tickets;                /* enable / disable session tickets         */
     opt.allow_sha1          = DFL_SHA1;
     opt.auth_mode           = DFL_AUTH_MODE;
     opt.cert_req_ca_list    = DFL_CERT_REQ_CA_LIST;
    opt.cert_req_dn_hint    = DFL_CERT_REQ_DN_HINT;
     opt.mfl_code            = DFL_MFL_CODE;
     opt.trunc_hmac          = DFL_TRUNC_HMAC;
     opt.tickets             = DFL_TICKETS;
         else if( strcmp( p, "cert_req_ca_list" ) == 0 )
         {
             opt.cert_req_ca_list = atoi( q );
            if( opt.cert_req_ca_list < 0 || opt.cert_req_ca_list > 3 )
                 goto usage;
            if( opt.cert_req_ca_list > 1 )
            {
                opt.cert_req_dn_hint = opt.cert_req_ca_list;
                opt.cert_req_ca_list = MBEDTLS_SSL_CERT_REQ_CA_LIST_ENABLED;
            }
         }
         else if( strcmp( p, "max_frag_len" ) == 0 )
         {
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
                 sig_alg_list[i++] = MBEDTLS_TLS1_3_SIG_ECDSA_SECP521R1_SHA512;
             }
            else if( strcmp( q, "rsa_pss_rsae_sha256" ) == 0 )
            {
                sig_alg_list[i++] = MBEDTLS_TLS1_3_SIG_RSA_PSS_RSAE_SHA256;
            }
            else if( strcmp( q, "rsa_pss_rsae_sha384" ) == 0 )
            {
                sig_alg_list[i++] = MBEDTLS_TLS1_3_SIG_RSA_PSS_RSAE_SHA384;
            }
            else if( strcmp( q, "rsa_pss_rsae_sha512" ) == 0 )
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
     if( opt.cert_req_ca_list != DFL_CERT_REQ_CA_LIST )
         mbedtls_ssl_conf_cert_req_ca_list( &conf, opt.cert_req_ca_list );
 
#if defined(MBEDTLS_X509_CRT_PARSE_C)
#if defined(MBEDTLS_KEY_EXCHANGE_CERT_REQ_ALLOWED_ENABLED)
    /* exercise setting DN hints for server certificate request
     * (Intended for use where the client cert expected has been signed by
     *  a specific CA which is an intermediate in a CA chain, not the root) */
    if( opt.cert_req_dn_hint == 2 && key_cert_init2 )
        mbedtls_ssl_conf_dn_hints( &conf, &srvcert2 );
#endif
#endif

 #if defined(MBEDTLS_SSL_PROTO_DTLS)
     if( opt.hs_to_min != DFL_HS_TO_MIN || opt.hs_to_max != DFL_HS_TO_MAX )
         mbedtls_ssl_conf_handshake_timeout( &conf, opt.hs_to_min, opt.hs_to_max );
     }
 #endif
 
#if defined(MBEDTLS_X509_CRT_PARSE_C)
#if defined(MBEDTLS_SSL_SERVER_NAME_INDICATION)
#if defined(MBEDTLS_KEY_EXCHANGE_CERT_REQ_ALLOWED_ENABLED)
    /* exercise setting DN hints for server certificate request
     * (Intended for use where the client cert expected has been signed by
     *  a specific CA which is an intermediate in a CA chain, not the root)
     * (Additionally, the CA choice would typically be influenced by SNI
     *  if being set per-handshake using mbedtls_ssl_set_hs_dn_hints()) */
    if( opt.cert_req_dn_hint == 3 && key_cert_init2 )
        mbedtls_ssl_set_hs_dn_hints( &ssl, &srvcert2 );
#endif
#endif
#endif

     mbedtls_printf( " ok\n" );
 
     /*