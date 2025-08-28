     err = json_val_object_get_elem_by_key(opt, L"uid", &elem);
     if (!err) {
         str = json_val_string_get(elem.value);
        json_val_free(elem.value);
         if (str == NULL)
             return ERR_TAG(ENOMEM);
         err = awcstombs(&buf, str, &s) == (size_t)-1 ? ERR_TAG(errno) : 0;
         if (err)
             return ERR_TAG(-err);
         str = json_val_string_get(elem.value);
        json_val_free(elem.value);
         if (str == NULL)
             return ERR_TAG(ENOMEM);
         omemset(&s, 0);
         if (err)
             return ERR_TAG(-err);
         str = json_val_string_get(elem.value);
        json_val_free(elem.value);
         if (str == NULL)
             return ERR_TAG(ENOMEM);
         err = awcstombs(&buf, str, &s) == (size_t)-1 ? ERR_TAG(errno) : 0;
         if (err)
             return ERR_TAG(-err);
         str = json_val_string_get(elem.value);
        json_val_free(elem.value);
         if (str == NULL)
             return ERR_TAG(ENOMEM);
         omemset(&s, 0);