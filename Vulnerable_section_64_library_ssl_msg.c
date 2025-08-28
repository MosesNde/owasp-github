             if( ++ssl->cur_out_ctr[i - 1] != 0 )
                 break;
 
        /* The loop goes to its end iff the counter is wrapping */
         if( i == mbedtls_ssl_ep_len( ssl ) )
         {
             MBEDTLS_SSL_DEBUG_MSG( 1, ( "outgoing message counter would wrap" ) );