 
     bn_ctx = BN_CTX_new();
     if (bn_ctx == NULL)
        goto err;
 
     BN_CTX_start(bn_ctx);
 