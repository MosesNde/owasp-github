     dbTable *table;
     dbColumn *column;
 
    Points = Vect_new_line_struct();
    Cats = Vect_new_cats_struct();
     db_init_string(&sql);
 
     Fi = Vect_get_field(Map, field);
     if (driver == NULL) {
         G_warning(_("Unable to open database <%s> by driver <%s>"),
                   Fi->database, Fi->driver);
         return 1;
     }
     db_set_error_handler_driver(driver);
 
     val =
     db_close_database_shutdown_driver(driver);
     Vect_destroy_line_struct(Points);
     Vect_destroy_cats_struct(Cats);
 
     return 0;
 }