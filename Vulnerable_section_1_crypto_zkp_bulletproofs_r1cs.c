 
     bn_ctx = BN_CTX_new();
     if (bn_ctx == NULL)
        return NULL;
 
     BN_CTX_start(bn_ctx);
 