 
     if (driver)
         db_close_database_shutdown_driver(driver);
    Vect_destroy_cats_struct(CCats);
    Vect_destroy_field_info(Fi);
 
     return 0;
 }