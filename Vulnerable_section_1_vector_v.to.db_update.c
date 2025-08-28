 #include <math.h>
 #include <grass/dbmi.h>
 #include <grass/glocale.h>
 #include "global.h"
 
 static int srch(const void *, const void *);
 
     db_close_database_shutdown_driver(driver);
     db_free_string(&stmt);
 
     return 0;
 }