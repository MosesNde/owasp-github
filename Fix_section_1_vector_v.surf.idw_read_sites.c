                                                  only when column is
                                                  not defined */
     if (!col) {
        const char *mname = Vect_get_full_name(&Map);
         if (!with_z)
             G_important_message(_("Input vector map <%s> is 2D - using "
                                   "categories to interpolate"),
                                mname);
         else
             G_important_message(_("Input vector map <%s> is 3D - using "
                                   "z-coordinates to interpolate"),
                                mname);
        G_free((void *)mname);
     }
 
     if (col) {
                           nrec);
 
         db_close_database_shutdown_driver(Driver);
        Vect_destroy_field_info(Fi);
     }
 
     Points = Vect_new_line_struct();
     Vect_close(&Map);
 
     G_message(n_("%ld point loaded", "%ld points loaded", npoints), npoints);
    Vect_destroy_line_struct(Points);
    Vect_destroy_cats_struct(Cats);
 }