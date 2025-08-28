     /* Destroy original key/value structure and replace with new one */
     G_free_key_value(projinfo);
     projinfo = temp_projinfo;
 
     return 1;
 }
                     do {
                         struct gpj_datum_transform_list *old = list;
 
                        if (list->count == datumtrans)
                             chosenparams = G_store(list->params);
                         list = list->next;
                         GPJ_free_datum_transform(old);
                     } while (list != NULL);