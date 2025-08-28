     Rast_quant_free(quant);
 
     if (Rast_map_type(name, mapset) == CELL_TYPE) {
        char *mname = G_fully_qualified_name(name, mapset);
         G_warning(_("Attempt to open quantization"
                     " table for CELL raster map <%s>"),
                  mname);
        G_free(mname);
         return -2;
     }
 
 
         /* int range doesn't exist anymore if (quant_load_range (quant, name,
          * mapset)>0) return 3; */
        char *mname = G_fully_qualified_name(name, mapset);
        G_warning(_("Quantization file for raster map <%s> is missing"), mname);
        G_free(mname);
     }
     else {
         parsStat = quant_parse_file(fd, quant);