 
     Points = Vect_new_line_struct();
     Vect_rewind(Map);
    const char *map_name = Vect_get_full_name(Map);
     G_verbose_message(_("Topology not available for vector map <%s>. "
                         "Registering primitives..."),
                      map_name);
    G_free((void *)map_name);
     while (TRUE) {
         /* register line */
         type = Vect_read_next_line(Map, Points, NULL);