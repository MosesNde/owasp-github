     long size;
     double *x, *y, *z;
 
    GEOSCoordSequence *pseq;
 
     G_debug(3, "V1_read_line_geos(): offset = %ld", offset);
 
     G_debug(3, "    n_points = %d dim = %d", n_points,
             (Map->head.with_z) ? 3 : 2);
 
    pseq = GEOSCoordSeq_create(n_points, (Map->head.with_z) ? 3 : 2);

     x = (double *)G_malloc(n_points * sizeof(double));
     y = (double *)G_malloc(n_points * sizeof(double));
     if (Map->head.with_z)
         z = (double *)G_malloc(n_points * sizeof(double));
     else
         z = NULL;
 
    if (0 >= dig__fread_port_D(x, n_points, &(Map->dig_fp)))
        return NULL; /* end of file */
 
    if (0 >= dig__fread_port_D(y, n_points, &(Map->dig_fp)))
        return NULL; /* end of file */
 
     if (Map->head.with_z) {
        if (0 >= dig__fread_port_D(z, n_points, &(Map->dig_fp)))
            return NULL; /* end of file */
     }
 
     for (i = 0; i < n_points; i++) {
         GEOSCoordSeq_setX(pseq, i, x[i]);
         GEOSCoordSeq_setY(pseq, i, y[i]);
 
     G_debug(3, "    off = %ld", (long)dig_ftell(&(Map->dig_fp)));
 
     G_free((void *)x);
     G_free((void *)y);
     if (z)