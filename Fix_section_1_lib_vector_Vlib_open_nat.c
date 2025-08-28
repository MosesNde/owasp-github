         Map->dig_fp.file = G_fopen_old(path, GV_COOR_ELEMENT, Map->mapset);
 
     if (Map->dig_fp.file == NULL) {
        const char *map_name = Vect_get_full_name(Map);
        G_warning(_("Unable to open coor file for vector map <%s>"), map_name);
        G_free((void *)map_name);
         return -1;
     }
 