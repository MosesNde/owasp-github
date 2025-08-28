     Cats = Vect_new_cats_struct();
 
     Vect_rewind(Map);
     G_message(_("Topology not available for vector map <%s>. "
                 "Registering primitives..."),
              Vect_get_full_name(Map));
     while (TRUE) {
         /* register line */
         type = Vect_read_next_line(Map, Points, Cats);