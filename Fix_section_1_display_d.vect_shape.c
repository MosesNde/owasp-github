 {
     int open_db, field, i, stat;
     dbCatValArray cvarr_rgb, cvarr_width, cvarr_size, cvarr_rot;
    struct field_info *fi = NULL;
     dbDriver *driver;
     int nrec_rgb, nrec_width, nrec_size, nrec_rot, have_colors;
     struct Colors colors, zcolors;
         }
     }
 
     if (z_style) {
         if (!Vect_is_3d(Map)) {
             G_warning(_("Vector map is not 3D. Unable to colorize features "
         cats_colors_flag, default_width, width_scale, z_style ? &zcolors : NULL,
         rgb_column ? &cvarr_rgb : NULL, have_colors ? &colors : NULL,
         &cvarr_width, nrec_width, &cvarr_size, nrec_size, &cvarr_rot, nrec_rot);
    if (open_db) {
        db_close_database_shutdown_driver(driver);
        Vect_destroy_field_info(fi);
    }
 
     return stat;
 }