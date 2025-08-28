 
     if (ctx->wasm_conf == NULL) {
         flb_plg_error(ctx->ins, "wasm_conf cannot be NULL");
         return -1;
     }
     ctx->wasm_conf->stdoutfd = fileno(stdoutp);