     Rast_quant_free(quant);
 
     if (Rast_map_type(name, mapset) == CELL_TYPE) {
         G_warning(_("Attempt to open quantization"
                     " table for CELL raster map <%s>"),
                  G_fully_qualified_name(name, mapset));
         return -2;
     }
 
 
         /* int range doesn't exist anymore if (quant_load_range (quant, name,
          * mapset)>0) return 3; */
        G_warning(_("Quantization file for raster map <%s> is missing"),
                  G_fully_qualified_name(name, mapset));
     }
     else {
         parsStat = quant_parse_file(fd, quant);