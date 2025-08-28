         ret = fw_prot_secure_forward_handshake_start(ctx->ins, connection, helo);
         if (ret != 0) {
             flb_free(helo);
             return NULL;
         }
 