 {
     int ctype, nrec, i;
     int red, grn, blu;
    int *pval;
     char buf[1024];
     struct field_info *fi;
     dbDriver *driver;
     nrec = db_select_int(driver, fi->table, fi->key, NULL, &pval);
     if (nrec < 1) {
         G_warning(_("No categories found"));
         return;
     }
 
     db_commit_transaction(driver);
 
     db_close_database_shutdown_driver(driver);
 }