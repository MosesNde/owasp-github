         *has_z = 1;
         ndim = 3;
     }
    char *mname = G_fully_qualified_name(name, mapset);
 
     while (eof == 0) {
         ltype = Vect_read_next_line(&map, Points, Cats);
         switch (ltype) {
         case -1: {
            G_warning(_("Unable to read vector map <%s>"), mname);
            G_free(mname);
            G_free(top);
            G_free(gpt);
             return NULL;
         }
         case -2: /* EOF */
     if (!np) {
         G_warning(
             _("No points from vector map <%s> fall within current region"),
            mname);
        G_free(mname);
        G_free(top);
         return (NULL);
     }
     else {
        G_message(_("Vector map <%s> loaded (%d points)"), mname, np);
        G_free(mname);
     }
 
     *nsites = np;
     int red, blu, grn;
     const char *str;
     const char *mapset;
    char *fname;
 
    dbDriver *driver = NULL;
     dbValue value;
 
     if (!gp || !gp->tstyle || !gp->filename)
             G_fatal_error(_("Unable to open database <%s> by driver <%s>"),
                           Fi->database, Fi->driver);
     }
    fname = G_fully_qualified_name(gp->filename, mapset);
    G_message(_("Loading thematic points layer <%s>..."), fname);
    G_free(fname);
     npts = nskipped = 0;
     for (gpt = gp->points; gpt; gpt = gpt->next) {
         gpt->style = (gvstyle *)G_malloc(sizeof(gvstyle));
                                 ((int)((blu) << 16) & BLU_MASK);
         }
         if (gp->tstyle->color_column) {
            if (driver) {
                nvals = db_select_value(driver, Fi->table, Fi->key, cat,
                                        gp->tstyle->color_column, &value);
                if (nvals < 1)
                    continue;
                str = db_get_value_string(&value);
                if (!str)
                    continue;
            }
             if (G_str_to_color(str, &red, &grn, &blu) != 1) {
                 G_warning(_("Invalid color definition (%s)"), str);
                 gpt->style->color = gp->style->color;
             _("%d points without category. "
               "Unable to determine color rules for features without category."),
             nskipped);
    if (driver)
        db_close_database_shutdown_driver(driver);
    Vect_destroy_field_info(Fi);
     return npts;
 }