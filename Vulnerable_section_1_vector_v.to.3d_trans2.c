         G_debug(3, "%d records selected", cvarr.n_values);
 
         db_close_database_shutdown_driver(driver);
     }
 
     G_message(_("Transforming features..."));