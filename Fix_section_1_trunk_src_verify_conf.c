             return ERR_TAG(EIO);
 
         str = json_string_get_value(val);
        json_val_free(val);
         if (str == NULL)
             return ERR_TAG(ENOMEM);
 