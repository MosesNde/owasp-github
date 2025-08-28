     p = OPENSSL_malloc((size_t)len);
     if (!msi_file_read(ctx->msi_ctx->msi, ds, 0, p, len)) {
         printf("DigitalSignature stream data error\n");
         return NULL;
     }
     blob = (u_char *)p;