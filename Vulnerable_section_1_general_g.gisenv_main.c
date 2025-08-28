 {
     char *u_name; /* uppercase variable name */
     char *name, *ptr;
 
     name = G_store(v_name);
     if (value)
     if (ptr != NULL) {
         *ptr = '\0';
         if (value)
            *value = ptr + 1;
     }
     /* Allow unset without '=' sign */
     if (value) {
        if (*value != NULL && **value == '\0')
             *value = NULL;
     }
     if (strlen(name) < 1)
         G_fatal_error(_("GRASS variable not defined"));
         G_verbose_message(_("GRASS variable must be uppercase. Using '%s'."),
                           u_name);
     }
 
     return u_name;
 }