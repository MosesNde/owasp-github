     ret = size;
 
 err:
    OPENSSL_free(buf);
     PAILLIER_CIPHERTEXT_free(r);
     return ret;
 }