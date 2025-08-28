     }
 
     fd = -1;
 
     if (G_find_file2_misc("cell_misc", "f_range", name, mapset)) {
         fd = G_open_old_misc("cell_misc", "f_range", name, mapset);
         if (fd < 0) {
            G_warning(_("Unable to read fp range file for <%s>"),
                      G_fully_qualified_name(name, mapset));
             return -1;
         }
 
         if (read(fd, xdr_buf, sizeof(xdr_buf)) != sizeof(xdr_buf)) {
             /* if the f_range file exists, but empty file, meaning Nulls */
             close(fd);
            G_debug(1, "Empty fp range file meaning Nulls for <%s>",
                    G_fully_qualified_name(name, mapset));
             return 2;
         }
 
     else {
         /* "f_range" file does not exist */
         G_warning(_("Missing fp range file for <%s> (run r.support -s)"),
                  G_fully_qualified_name(name, mapset));
         return -1;
     }
 
     return 1;
 }
 
     Rast_init_range(range);
     fd = NULL;
 
     /* if map is not integer, read quant rules, and get limits */
     if (Rast_map_type(name, mapset) != CELL_TYPE) {
         DCELL dmin, dmax;
 
         if (Rast_read_quant(name, mapset, &quant) < 0) {
             G_warning(_("Unable to read quant rules for raster map <%s>"),
                      G_fully_qualified_name(name, mapset));
             return -1;
         }
         if (Rast_quant_is_truncate(&quant) || Rast_quant_is_round(&quant)) {
                         x[1] = (CELL)(dmax - .5);
                 }
             }
            else
                 return -1;
         }
         else
             Rast_quant_get_limits(&quant, &dmin, &dmax, &x[0], &x[1]);
 
         Rast_update_range(x[0], range);
         Rast_update_range(x[1], range);
         return 3;
     }
 
     if (G_find_file2_misc("cell_misc", "range", name, mapset)) {
         fd = G_fopen_old_misc("cell_misc", "range", name, mapset);
         if (!fd) {
            G_warning(_("Unable to read range file for <%s>"),
                      G_fully_qualified_name(name, mapset));
             return -1;
         }
 
         /* if range file exists but empty */
         if (!fgets(buf, sizeof buf, fd)) {
             if (fd)
                 fclose(fd);
             return 2;
         }
 
 
             G_warning(_("Unable to read range file for <%s>"),
                       G_fully_qualified_name(name, mapset));
             return -1;
         }
 
     }
     else {
         /* "range" file does not exist */
        G_warning(_("Missing range file for <%s> (run r.support -s)"),
                  G_fully_qualified_name(name, mapset));
         return -1;
     }
 
     return 1;
 }
         return -1;
     }
 
     fd = G_open_old_misc("cell_misc", "stats", name, mapset);
     if (fd < 0) {
        G_warning(_("Unable to read stats file for <%s>"),
                  G_fully_qualified_name(name, mapset));
         return -1;
     }
 
     if (read(fd, xdr_buf, sizeof(xdr_buf)) != sizeof(xdr_buf)) {
         /* if the stats file exists, but empty file, meaning Nulls */
         close(fd);
        G_debug(1, "Empty stats file meaning Nulls for <%s>",
                G_fully_qualified_name(name, mapset));
         return 2;
     }
 
     if (read(fd, &nbytes, 1) != 1) {
         /* if the stats file exists, but empty file, meaning Nulls */
         close(fd);
        G_debug(1, "Unable to read byte count in stats file for <%s>",
                G_fully_qualified_name(name, mapset));
         return -1;
     }
 
     count = 0;
    if (nbytes == 0)
         return 1;
 
     if (nbytes < 1 || (unsigned char)nbytes > sizeof(grass_int64)) {
         close(fd);
        G_debug(1, "Invalid byte count in stats file for <%s>",
                G_fully_qualified_name(name, mapset));
         return -1;
     }
     if (read(fd, cc, nbytes) != nbytes) {
         /* incorrect number of bytes for count */
         close(fd);
        G_debug(1, "Unable to read count in stats file for <%s>",
                G_fully_qualified_name(name, mapset));
         return -1;
     }
 
     rstats->count = count;
 
     close(fd);
 
     return 1;
 }