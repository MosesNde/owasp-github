 
         if (n > varray->size) { /* not enough space */
             G_warning(_("Not enough space in vector array"));
             return 0;
         }
 
 
         if (n > varray->size) { /* not enough space */
             G_warning(_("Not enough space in vector array"));
             return 0;
         }
 
         return 0;
     }
 
    Cats = Vect_new_cats_struct();

     /* Select categories from DB to array */
     Fi = Vect_get_field(Map, field);
     if (Fi == NULL) {
     if (driver == NULL) {
         G_warning(_("Unable to open database <%s> by driver <%s>"),
                   Fi->database, Fi->driver);
         return -1;
     }
 
         G_warning(
             _("Unable to select record from table <%s> (key %s, where %s)"),
             Fi->table, Fi->key, where);
         return -1;
     }
 
     if (type & GV_AREA) { /* Areas */
         n = Vect_get_num_areas(Map);
            it for all features. */
         if (n > varray->size) { /* not enough space */
             G_warning(_("Not enough space in vector array"));
             return 0;
         }
 
 
         if (n > varray->size) { /* not enough space */
             G_warning(_("Not enough space in vector array"));
             return 0;
         }
 