                                  &cvarr);
     if (nrec < 1) {
         G_important_message(_("No data selected"));
        Vect_destroy_field_info(fi);
        db_close_database(driver);
         return 0;
     }
 
     }
 
     db_close_database(driver);
    Vect_destroy_field_info(fi);
 
     return is_fp;
 }