                                  &cvarr);
     if (nrec < 1) {
         G_important_message(_("No data selected"));
         return 0;
     }
 
     }
 
     db_close_database(driver);
 
     return is_fp;
 }