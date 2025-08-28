             return ERR_TAG(-err);
 
         opt = &opts[hash_wcs(elem.key, -1) >> 3 & 63];
        if (opt->opt == NULL || wcscmp(elem.key, opt->opt) != 0) {
            json_val_free(elem.value);
             return ERR_TAG(EIO);
        }
 
         err = (*opt->fn)(elem.value, ctx);
        json_val_free(elem.value);
         if (err)
             return err;
     }