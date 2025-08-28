 {
     struct Cell_head loc_wind;
     struct Key_Value *proj_info = NULL, *proj_units = NULL;
     char *wkt = NULL, *srid = NULL;
     char error_msg[8096];
     int proj_trouble;
         }
     }
     else {
        struct Key_Value *loc_proj_info = NULL, *loc_proj_units = NULL;
         int err = 0;
         void (*msg_fn)(const char *, ...);
 
                 exit(EXIT_SUCCESS);
             }
         }
        G_free_key_value(loc_proj_units);
        G_free_key_value(loc_proj_info);
     }
    G_free_key_value(proj_info);
    G_free_key_value(proj_units);
 }