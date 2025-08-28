     dbTable *table;
     dbColumn *column;
 
     db_init_string(&sql);
 
     Fi = Vect_get_field(Map, field);
     if (driver == NULL) {
         G_warning(_("Unable to open database <%s> by driver <%s>"),
                   Fi->database, Fi->driver);
        Vect_destroy_field_info(Fi);
         return 1;
     }
    Points = Vect_new_line_struct();
    Cats = Vect_new_cats_struct();
     db_set_error_handler_driver(driver);
 
     val =
     db_close_database_shutdown_driver(driver);
     Vect_destroy_line_struct(Points);
     Vect_destroy_cats_struct(Cats);
    Vect_destroy_field_info(Fi);
    G_free(val);
 
     return 0;
 }