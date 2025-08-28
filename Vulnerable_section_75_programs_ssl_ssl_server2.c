 #define DFL_CID_VALUE_RENEGO    NULL
 #define DFL_AUTH_MODE           -1
 #define DFL_CERT_REQ_CA_LIST    MBEDTLS_SSL_CERT_REQ_CA_LIST_ENABLED
 #define DFL_MFL_CODE            MBEDTLS_SSL_MAX_FRAG_LEN_NONE
 #define DFL_TRUNC_HMAC          -1
 #define DFL_TICKETS             MBEDTLS_SSL_SESSION_TICKETS_ENABLED
     "                        options: none, optional, required\n" \
     "    cert_req_ca_list=%%d default: 1 (send ca list)\n"  \
     "                        options: 1 (send ca list), 0 (don't send)\n" \
     USAGE_IO                                                \
     USAGE_KEY_OPAQUE                                        \
     "\n"                                                    \
     int allow_sha1;             /* flag for SHA-1 support                   */
     int auth_mode;              /* verify mode for connection               */
     int cert_req_ca_list;       /* should we send the CA list?              */
     unsigned char mfl_code;     /* code for maximum fragment length         */
     int trunc_hmac;             /* accept truncated hmac?                   */
     int tickets;                /* enable / disable session tickets         */
     opt.allow_sha1          = DFL_SHA1;
     opt.auth_mode           = DFL_AUTH_MODE;
     opt.cert_req_ca_list    = DFL_CERT_REQ_CA_LIST;
     opt.mfl_code            = DFL_MFL_CODE;
     opt.trunc_hmac          = DFL_TRUNC_HMAC;
     opt.tickets             = DFL_TICKETS;
         else if( strcmp( p, "cert_req_ca_list" ) == 0 )
         {
             opt.cert_req_ca_list = atoi( q );
            if( opt.cert_req_ca_list < 0 || opt.cert_req_ca_list > 1 )
                 goto usage;
         }
         else if( strcmp( p, "max_frag_len" ) == 0 )
         {
             if( *p == ',' )
                 *p++ = '\0';
 
            if( strcmp( q, "ecdsa_secp256r1_sha256" ) == 0 )
             {
                 sig_alg_list[i++] = MBEDTLS_TLS1_3_SIG_ECDSA_SECP256R1_SHA256;
             }
             {
                 sig_alg_list[i++] = MBEDTLS_TLS1_3_SIG_ECDSA_SECP521R1_SHA512;
             }
             else
             {
                mbedtls_printf( "unknown signature algorithm %s\n", q );
                mbedtls_printf( "supported signature algorithms: " );
                mbedtls_printf( "ecdsa_secp256r1_sha256 " );
                mbedtls_printf( "ecdsa_secp384r1_sha384 " );
                mbedtls_printf( "ecdsa_secp521r1_sha512 " );
                mbedtls_printf( "\n" );
                 goto exit;
             }
         }
     if( opt.cert_req_ca_list != DFL_CERT_REQ_CA_LIST )
         mbedtls_ssl_conf_cert_req_ca_list( &conf, opt.cert_req_ca_list );
 
 #if defined(MBEDTLS_SSL_PROTO_DTLS)
     if( opt.hs_to_min != DFL_HS_TO_MIN || opt.hs_to_max != DFL_HS_TO_MAX )
         mbedtls_ssl_conf_handshake_timeout( &conf, opt.hs_to_min, opt.hs_to_max );
     }
 #endif
 
     mbedtls_printf( " ok\n" );
 
     /*