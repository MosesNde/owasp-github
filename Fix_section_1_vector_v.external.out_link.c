         G_verbose_message(_("Switched to PostGIS format"));
 
     G_free_key_value(key_val);
    G_free(dsn);
 }
 
 int parse_option_pg(const char *option, char **key, char **value)