     /* close level 1 files / data sources if not head_only */
     if (!Map->head_only) {
         if (create_link && ((*Close_array[Map->format][1])(Map)) != 0) {
            G_warning(_("Unable to close vector <%s>"),
                      Vect_get_full_name(Map));
             return 1;
         }
     }