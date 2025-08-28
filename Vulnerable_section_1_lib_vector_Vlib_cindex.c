 
     if (0 > dig_write_cidx(&fp, plus)) {
         G_warning(_("Error writing out category index file"));
         return 1;
     }
 
     fp.file = G_fopen_old(path, GV_CIDX_ELEMENT, Map->mapset);
 
     if (fp.file == NULL) { /* category index file is not available */
         G_warning(_("Unable to open category index file for vector map <%s>"),
                  Vect_get_full_name(Map));
         return -1;
     }
 