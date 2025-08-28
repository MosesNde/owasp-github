 
     if (0 > dig_write_cidx(&fp, plus)) {
         G_warning(_("Error writing out category index file"));
        fclose(fp.file);
         return 1;
     }
 
     fp.file = G_fopen_old(path, GV_CIDX_ELEMENT, Map->mapset);
 
     if (fp.file == NULL) { /* category index file is not available */
        const char *map_name = Vect_get_full_name(Map);
         G_warning(_("Unable to open category index file for vector map <%s>"),
                  map_name);
        G_free((void *)map_name);
         return -1;
     }
 