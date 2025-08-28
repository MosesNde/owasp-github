         return Map->fInfo.pg.db_name;
     }
 
    const char *mname = Vect_get_full_name(Map);
    G_debug(1, "Native vector format detected for <%s>", mname);
    G_free((void *)mname);
 
     return NULL;
 }
                    Map->fInfo.pg.table_name);
     }
     else {
        const char *mname = Vect_get_full_name(Map);
        G_debug(1, "Native vector format detected for <%s>", mname);
        G_free((void *)mname);
     }
 
     return name;