             return ERR_TAG(-err);
 
         opt = &opts[hash_wcs(elem.key, -1) >> 3 & 63];
        if (opt->opt == NULL || wcscmp(elem.key, opt->opt) != 0)
             return ERR_TAG(EIO);
 
         err = (*opt->fn)(elem.value, ctx);
         if (err)
             return err;
     }