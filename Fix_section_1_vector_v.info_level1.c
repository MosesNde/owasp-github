     Cats = Vect_new_cats_struct();
 
     Vect_rewind(Map);
    const char *mname = Vect_get_full_name(Map);
     G_message(_("Topology not available for vector map <%s>. "
                 "Registering primitives..."),
              mname);
    G_free((void *)mname);
     while (TRUE) {
         /* register line */
         type = Vect_read_next_line(Map, Points, Cats);