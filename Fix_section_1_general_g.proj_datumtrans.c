     /* Destroy original key/value structure and replace with new one */
     G_free_key_value(projinfo);
     projinfo = temp_projinfo;
    G_free(dstruct.ellps);
    G_free(dstruct.longname);
    G_free(dstruct.name);
 
     return 1;
 }
                     do {
                         struct gpj_datum_transform_list *old = list;
 
                        if (list->count == datumtrans) {
                            G_free(chosenparams);
                             chosenparams = G_store(list->params);
                        }
                         list = list->next;
                         GPJ_free_datum_transform(old);
                     } while (list != NULL);