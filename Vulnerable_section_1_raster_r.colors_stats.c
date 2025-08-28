         cell = Rast_allocate_c_buf();
         nrows = Rast_window_rows();
         ncols = Rast_window_cols();
 
         G_verbose_message(_("(%i/%i) Reading raster map <%s>..."), i + 1,
                          input_maps->num,
                          G_fully_qualified_name(input_maps->names[i],
                                                 input_maps->mapsets[i]));
 
         for (row = 0; row < nrows; row++) {
             G_percent(row, nrows, 2);
             ncols = map3d->window.cols;
             ndepths = map3d->window.depths;
         }

         G_verbose_message(_("(%i/%i) Reading map <%s>..."), i, input_maps->num,
                          G_fully_qualified_name(name, mapset));
 
         for (depth = 0; depth < ndepths; depth++) {
             for (row = 0; row < nrows; row++) {