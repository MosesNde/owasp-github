         *has_z = 1;
         ndim = 3;
     }
 
     while (eof == 0) {
         ltype = Vect_read_next_line(&map, Points, Cats);
         switch (ltype) {
         case -1: {
            G_warning(_("Unable to read vector map <%s>"),
                      G_fully_qualified_name(name, mapset));
             return NULL;
         }
         case -2: /* EOF */
     if (!np) {
         G_warning(
             _("No points from vector map <%s> fall within current region"),
            G_fully_qualified_name(name, mapset));
         return (NULL);
     }
     else {
        G_message(_("Vector map <%s> loaded (%d points)"),
                  G_fully_qualified_name(name, mapset), np);
     }
 
     *nsites = np;
     int red, blu, grn;
     const char *str;
     const char *mapset;
 
    dbDriver *driver;
     dbValue value;
 
     if (!gp || !gp->tstyle || !gp->filename)
             G_fatal_error(_("Unable to open database <%s> by driver <%s>"),
                           Fi->database, Fi->driver);
     }
    G_message(_("Loading thematic points layer <%s>..."),
              G_fully_qualified_name(gp->filename, mapset));
     npts = nskipped = 0;
     for (gpt = gp->points; gpt; gpt = gpt->next) {
         gpt->style = (gvstyle *)G_malloc(sizeof(gvstyle));
                                 ((int)((blu) << 16) & BLU_MASK);
         }
         if (gp->tstyle->color_column) {
            nvals = db_select_value(driver, Fi->table, Fi->key, cat,
                                    gp->tstyle->color_column, &value);
            if (nvals < 1)
                continue;
            str = db_get_value_string(&value);
            if (!str)
                continue;
             if (G_str_to_color(str, &red, &grn, &blu) != 1) {
                 G_warning(_("Invalid color definition (%s)"), str);
                 gpt->style->color = gp->style->color;
             _("%d points without category. "
               "Unable to determine color rules for features without category."),
             nskipped);
     return npts;
 }