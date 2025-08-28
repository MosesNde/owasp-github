         cell = Rast_allocate_c_buf();
         nrows = Rast_window_rows();
         ncols = Rast_window_cols();
        char *mname = G_fully_qualified_name(input_maps->names[i],
                                             input_maps->mapsets[i]);
 
         G_verbose_message(_("(%i/%i) Reading raster map <%s>..."), i + 1,
                          input_maps->num, mname);
        G_free(mname);
 
         for (row = 0; row < nrows; row++) {
             G_percent(row, nrows, 2);
             ncols = map3d->window.cols;
             ndepths = map3d->window.depths;
         }
        char *mname = G_fully_qualified_name(name, mapset);
         G_verbose_message(_("(%i/%i) Reading map <%s>..."), i, input_maps->num,
                          mname);
        G_free(mname);
 
         for (depth = 0; depth < ndepths; depth++) {
             for (row = 0; row < nrows; row++) {