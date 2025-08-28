     if (bn_ctx == NULL)
         goto err;
 
     a = BN_CTX_get(bn_ctx);
     e = BN_CTX_get(bn_ctx);
     t = BN_CTX_get(bn_ctx);
     ret = proof;
     proof = NULL;
 err:
     BN_CTX_free(bn_ctx);
     NIZK_DLOG_KNOWLEDGE_PROOF_free(proof);
     ZKP_TRANSCRIPT_reset(transcript);
     if (bn_ctx == NULL)
         goto err;
 
     e = BN_CTX_get(bn_ctx);
     bn1 = BN_CTX_get(bn_ctx);
     bn_1 = BN_CTX_get(bn_ctx);
 
     ret = 1;
 err:
     EC_POINT_free(L);
     EC_POINT_free(R);
     zkp_poly_points_free(poly);