                               struct Map_info *Out)
 {
     int ret, format, topo;
 
     if (Vect_level(In) < 1)
         G_fatal_error(
         /* copy features */
         ret += copy_lines_2(In, field, topo, Out);
 
        if (topo == TOPO_NONE &&
             /* check output feature type, centroids can be exported as
              * points; boundaries as linestrings */
            strcmp(Vect_get_finfo_geometry_type(Out), "polygon") == 0) {
            /* copy areas - external formats and simple features access only */
            ret += Vect__copy_areas(In, field, Out);
         }
     }
     else {
         /* -> copy features on level 1 */
        if (topo == TOPO_NONE)
             G_warning(_("Vector map <%s> not open on topological level. "
                         "Areas will be skipped!"),
                      Vect_get_full_name(In));
 
         ret += copy_lines_1(In, field, Out);
     }

     return ret > 0 ? 1 : 0;
 }
 
 int copy_lines_1(struct Map_info *In, int field, struct Map_info *Out)
 {
     int ret, type;
 
     struct line_pnts *Points;
     struct line_cats *Cats;
     while (TRUE) {
         type = Vect_read_next_line(In, Points, Cats);
         if (type == -1) {
            G_warning(_("Unable to read vector map <%s>"),
                      Vect_get_full_name(In));
             ret = 1;
             break;
         }
 
         Vect_write_line(Out, type, Points, Cats);
     }

     Vect_destroy_line_struct(Points);
     Vect_destroy_cats_struct(Cats);
 
     struct line_cats *Cats, *CCats;
 
     const char *ftype = NULL;
 
     Points = Vect_new_line_struct();
     CPoints = Vect_new_line_struct();
         G_percent(i, nlines, 2);
         type = Vect_read_line(In, Points, Cats, i);
         if (type == -1) {
            G_warning(_("Unable to read vector map <%s>"),
                      Vect_get_full_name(In));
             ret = 1;
             break; /* free allocated space and return */
         }
 
         if (-1 == Vect_write_line(Out, type, Points, Cats)) {
             G_warning(_("Writing new feature failed"));
            return 1;
         }
     }
 
     if (nskipped > 0)
         G_important_message(
             _("%d features without category or from different layer skipped"),
             nskipped);

     Vect_destroy_line_struct(Points);
     Vect_destroy_line_struct(CPoints);
     Vect_destroy_line_struct(NPoints);
     Vect_destroy_cats_struct(Cats);
     Vect_destroy_cats_struct(CCats);
 
     return ret;
 }
 int Vect__copy_areas(struct Map_info *In, int field, struct Map_info *Out)
 {
     int i, area, nareas, cat, isle, nisles, nparts_alloc, nskipped;
     struct line_pnts **Points;
     struct line_cats *Cats;
 
             if (0 > V2__write_area_sfa(Out, (const struct line_pnts **)Points,
                                        nisles + 1, Cats)) {
                 G_warning(_("Writing area %d failed"), area);
                return -1;
             }
         }
 #ifdef HAVE_POSTGRES
         else { /* building simple features geometry from topogeometry data */
             if (0 > V2__update_area_pg(Out, (const struct line_pnts **)Points,
                                        nisles + 1, cat)) {
                 G_warning(_("Writing area %d failed"), area);
                return -1;
             }
         }
 #endif
             nskipped);
 
     /* free allocated space for isles */
     for (i = 0; i < nparts_alloc; i++)
         Vect_destroy_line_struct(Points[i]);
     Vect_destroy_cats_struct(Cats);
 
    return 0;
 }
 
 /*!
 {
     int i, n, type;
     struct field_info *Fi;
 
     n = Vect_get_num_dblinks(In);
 
                       In->dblnk->field[i].number);
             return -1;
         }
        if (field > 0 && Fi->number != field)
             continue;
 
         if (Vect_copy_table(In, Out, Fi->number, Fi->number, Fi->name, type) !=
             0) {

             G_warning(
                 _("Unable to copy table <%s> for layer %d from <%s> to <%s>"),
                Fi->table, Fi->number, Vect_get_full_name(In),
                Vect_get_name(Out));
             return -1;
         }
     }

     return 0;
 }
 
                             int field_in, int field_out, const char *field_name,
                             int type, int *cats, int ncats)
 {
    int ret;
     struct field_info *Fi, *Fin;
     const char *name, *key;
    dbDriver *driver;
 
     G_debug(2, "Vect_copy_table_by_cats(): field_in = %d field_out = %d",
             field_in, field_out);
     if (ret == -1) {
         G_warning(_("Unable to add database link for vector map <%s>"),
                   Out->name);
        return -1;
     }
 
     if (cats)
                                 Fin->table, key, cats, ncats);
     if (ret == DB_FAILED) {
         G_warning(_("Unable to copy table <%s>"), Fin->table);
        return -1;
     }
 
     driver = db_start_driver_open_database(Fin->driver,
     if (!driver) {
         G_warning(_("Unable to open database <%s> with driver <%s>"),
                   Fin->database, Fin->driver);
        return -1;
     }
 
     /* do not allow duplicate keys */
     if (db_create_index2(driver, Fin->table, Fi->key) != DB_OK) {
         G_warning(_("Unable to create index"));
        return -1;
     }
 
     if (db_grant_on_table(driver, Fin->table, DB_PRIV_SELECT,
                           DB_GROUP | DB_PUBLIC) != DB_OK) {
         G_warning(_("Unable to grant privileges on table <%s>"), Fin->table);
        return -1;
     }
 
     db_close_database_shutdown_driver(driver);
 
    return 0;
 }