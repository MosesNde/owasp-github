     ret = size;
 
 err:
     PAILLIER_CIPHERTEXT_free(r);
     return ret;
 }