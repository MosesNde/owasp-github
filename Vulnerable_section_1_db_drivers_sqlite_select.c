                               db_get_string(sel),
                               (char *)sqlite3_errmsg(sqlite));
             db_d_report_error();
             return DB_FAILED;
         }
 
                               (char *)sqlite3_errmsg(sqlite));
             db_d_report_error();
             sqlite3_finalize(c->statement);
             return DB_FAILED;
         }
         else