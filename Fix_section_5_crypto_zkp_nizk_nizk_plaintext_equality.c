     if (bn_ctx == NULL)
         goto err;
 
    BN_CTX_start(bn_ctx);
     e = BN_CTX_get(bn_ctx);
     bn1 = BN_CTX_get(bn_ctx);
     if (bn1 == NULL)
 
     ret = 1;
 err:
    BN_CTX_end(bn_ctx);
    BN_CTX_free(bn_ctx);
     EC_POINT_free(L);
     EC_POINT_free(R);
     zkp_poly_points_free(poly);