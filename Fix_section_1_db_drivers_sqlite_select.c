                               db_get_string(sel),
                               (char *)sqlite3_errmsg(sqlite));
             db_d_report_error();
            G_free(str);
             return DB_FAILED;
         }
 
                               (char *)sqlite3_errmsg(sqlite));
             db_d_report_error();
             sqlite3_finalize(c->statement);
            G_free(str);
             return DB_FAILED;
         }
         else