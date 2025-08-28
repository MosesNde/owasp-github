 
         if (n > varray->size) { /* not enough space */
             G_warning(_("Not enough space in vector array"));
            Vect_destroy_cats_struct(Cats);
             return 0;
         }
 
 
         if (n > varray->size) { /* not enough space */
             G_warning(_("Not enough space in vector array"));
            Vect_destroy_cats_struct(Cats);
             return 0;
         }
 
         return 0;
     }
 
     /* Select categories from DB to array */
     Fi = Vect_get_field(Map, field);
     if (Fi == NULL) {
     if (driver == NULL) {
         G_warning(_("Unable to open database <%s> by driver <%s>"),
                   Fi->database, Fi->driver);
        Vect_destroy_field_info(Fi);
         return -1;
     }
 
         G_warning(
             _("Unable to select record from table <%s> (key %s, where %s)"),
             Fi->table, Fi->key, where);
        Vect_destroy_field_info(Fi);
         return -1;
     }
    Vect_destroy_field_info(Fi);
    Cats = Vect_new_cats_struct();
 
     if (type & GV_AREA) { /* Areas */
         n = Vect_get_num_areas(Map);
            it for all features. */
         if (n > varray->size) { /* not enough space */
             G_warning(_("Not enough space in vector array"));
            Vect_destroy_cats_struct(Cats);
            G_free(cats);
             return 0;
         }
 
 
         if (n > varray->size) { /* not enough space */
             G_warning(_("Not enough space in vector array"));
            Vect_destroy_cats_struct(Cats);
            G_free(cats);
             return 0;
         }
 