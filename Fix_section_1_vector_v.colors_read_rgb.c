         G_warning(_("%d invalid RGB color values skipped"), nskipped);
 
     db_close_database_shutdown_driver(driver);
    Vect_destroy_field_info(fi);
 }