     if (bn_ctx == NULL)
         goto err;
 
     e = BN_CTX_get(bn_ctx);
     bn1 = BN_CTX_get(bn_ctx);
     if (bn1 == NULL)
 
     ret = 1;
 err:
     EC_POINT_free(L);
     EC_POINT_free(R);
     zkp_poly_points_free(poly);
     ZKP_TRANSCRIPT_reset(transcript);
     return ret;
 }
