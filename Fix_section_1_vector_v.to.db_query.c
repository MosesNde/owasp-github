     }
 
     db_close_database_shutdown_driver(driver);
    Vect_destroy_line_struct(Points);
    Vect_destroy_cats_struct(Cats);
    Vect_destroy_field_info(Fi);
 
     return 0;
 }