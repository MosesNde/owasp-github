                                                  only when column is
                                                  not defined */
     if (!col) {
         if (!with_z)
             G_important_message(_("Input vector map <%s> is 2D - using "
                                   "categories to interpolate"),
                                Vect_get_full_name(&Map));
         else
             G_important_message(_("Input vector map <%s> is 3D - using "
                                   "z-coordinates to interpolate"),
                                Vect_get_full_name(&Map));
     }
 
     if (col) {
                           nrec);
 
         db_close_database_shutdown_driver(Driver);
     }
 
     Points = Vect_new_line_struct();
     Vect_close(&Map);
 
     G_message(n_("%ld point loaded", "%ld points loaded", npoints), npoints);
 }