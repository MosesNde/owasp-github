         G_debug(3, "%d records selected", cvarr.n_values);
 
         db_close_database_shutdown_driver(driver);
        Vect_destroy_field_info(Fi);
     }
 
     G_message(_("Transforming features..."));