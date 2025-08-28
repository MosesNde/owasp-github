     }
     ok = 1;
 end:
    OPENSSL_free(password);
    OPENSSL_free(salt);
     OSSL_SELF_TEST_free(ev);
     OPENSSL_free(module_checksum);
 