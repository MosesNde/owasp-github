     db_init_string(&text);
 
     fi = Vect_get_field(Map, lattr->field);
    if (fi == NULL) {
        Vect_destroy_line_struct(Points);
        Vect_destroy_cats_struct(Cats);
         return 1;
    }
     driver = db_start_driver_open_database(fi->driver, fi->database);
     if (driver == NULL)
         G_fatal_error(_("Unable to open database <%s> by driver <%s>"),
     db_close_database_shutdown_driver(driver);
     Vect_destroy_line_struct(Points);
     Vect_destroy_cats_struct(Cats);
    Vect_destroy_field_info(fi);
 
     return 0;
 }