         Map->dig_fp.file = G_fopen_old(path, GV_COOR_ELEMENT, Map->mapset);
 
     if (Map->dig_fp.file == NULL) {
        G_warning(_("Unable to open coor file for vector map <%s>"),
                  Vect_get_full_name(Map));
         return -1;
     }
 