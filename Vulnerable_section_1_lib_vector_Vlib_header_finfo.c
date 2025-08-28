         return Map->fInfo.pg.db_name;
     }
 
    G_debug(1, "Native vector format detected for <%s>",
            Vect_get_full_name(Map));
 
     return NULL;
 }
                    Map->fInfo.pg.table_name);
     }
     else {
        G_debug(1, "Native vector format detected for <%s>",
                Vect_get_full_name(Map));
     }
 
     return name;