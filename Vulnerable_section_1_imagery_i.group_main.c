             skip = 1;
             continue;
         }
 
        G_message(_("Adding raster map <%s> to group"),
                  G_fully_qualified_name(rasters[m], mapset));
 
         /* Go through existing files to check for duplicates */
         for (n = 0; n < ref.nfiles; n++) {
             if (strcmp(rasters[m], ref.file[n].name) == 0) {
                 G_message(_("Raster map <%s> exists in group. Skipped."),
                          G_fully_qualified_name(rasters[m], mapset));
                 skip = 1;
                 continue;
             }
         }
 
         if (skip == 0)
             I_add_file_to_group_ref(rasters[m], mapset, &ref);
     }
 
     G_debug(1, "writing group REF");
             skip = 1;
             continue;
         }
 
        G_message(_("Adding raster map <%s> to subgroup"),
                  G_fully_qualified_name(rasters[m], mapset));
 
         /* Go through existing files to check for duplicates */
         for (n = 0; n < ref.nfiles; n++) {
             if (strcmp(rasters[m], ref.file[n].name) == 0) {
                 G_message(_("Raster map <%s> exists in subgroup. Skipping..."),
                          G_fully_qualified_name(rasters[m], mapset));
                 skip = 1;
                 continue;
             }
         }
         if (skip == 0)
             I_add_file_to_group_ref(rasters[m], mapset, &ref);
     }
 
     G_debug(1, "writing subgroup REF");