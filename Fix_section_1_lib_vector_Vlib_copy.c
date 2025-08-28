                               struct Map_info *Out)
 {
     int ret, format, topo;
    const char *geometry_type = NULL;
    const char *map_name = NULL;
 
     if (Vect_level(In) < 1)
         G_fatal_error(
         /* copy features */
         ret += copy_lines_2(In, field, topo, Out);
 
        if (topo == TOPO_NONE) {
             /* check output feature type, centroids can be exported as
              * points; boundaries as linestrings */
            geometry_type = Vect_get_finfo_geometry_type(Out);
            if (geometry_type && strcmp(geometry_type, "polygon") == 0) {
                /* copy areas - external formats and simple features access only
                 */
                ret += Vect__copy_areas(In, field, Out);
            }
            G_free((void *)geometry_type);
         }
     }
     else {
         /* -> copy features on level 1 */
        if (topo == TOPO_NONE) {
            map_name = Vect_get_full_name(In);
             G_warning(_("Vector map <%s> not open on topological level. "
                         "Areas will be skipped!"),
                      map_name);
            G_free((void *)map_name);
        }
 
         ret += copy_lines_1(In, field, Out);
     }
     return ret > 0 ? 1 : 0;
 }
 
 int copy_lines_1(struct Map_info *In, int field, struct Map_info *Out)
 {
     int ret, type;
    const char *map_name = NULL;
 
     struct line_pnts *Points;
     struct line_cats *Cats;
     while (TRUE) {
         type = Vect_read_next_line(In, Points, Cats);
         if (type == -1) {
            map_name = Vect_get_full_name(In);
            G_warning(_("Unable to read vector map <%s>"), map_name);
            G_free((void *)map_name);
             ret = 1;
             break;
         }
 
         Vect_write_line(Out, type, Points, Cats);
     }
     Vect_destroy_line_struct(Points);
     Vect_destroy_cats_struct(Cats);
 
     struct line_cats *Cats, *CCats;
 
     const char *ftype = NULL;
    const char *map_name = NULL;
 
     Points = Vect_new_line_struct();
     CPoints = Vect_new_line_struct();
         G_percent(i, nlines, 2);
         type = Vect_read_line(In, Points, Cats, i);
         if (type == -1) {
            map_name = Vect_get_full_name(In);
            G_warning(_("Unable to read vector map <%s>"), map_name);
            G_free((void *)map_name);
             ret = 1;
             break; /* free allocated space and return */
         }
 
         if (-1 == Vect_write_line(Out, type, Points, Cats)) {
             G_warning(_("Writing new feature failed"));
            ret = 1;
            goto free_exit;
         }
     }
 
     if (nskipped > 0)
         G_important_message(
             _("%d features without category or from different layer skipped"),
             nskipped);
free_exit:
     Vect_destroy_line_struct(Points);
     Vect_destroy_line_struct(CPoints);
     Vect_destroy_line_struct(NPoints);
     Vect_destroy_cats_struct(Cats);
     Vect_destroy_cats_struct(CCats);
    G_free((void *)ftype);
 
     return ret;
 }
 int Vect__copy_areas(struct Map_info *In, int field, struct Map_info *Out)
 {
     int i, area, nareas, cat, isle, nisles, nparts_alloc, nskipped;
    int ret = 0;
     struct line_pnts **Points;
     struct line_cats *Cats;
 
             if (0 > V2__write_area_sfa(Out, (const struct line_pnts **)Points,
                                        nisles + 1, Cats)) {
                 G_warning(_("Writing area %d failed"), area);
                ret = -1;
                goto free_exit;
             }
         }
 #ifdef HAVE_POSTGRES
         else { /* building simple features geometry from topogeometry data */
             if (0 > V2__update_area_pg(Out, (const struct line_pnts **)Points,
                                        nisles + 1, cat)) {
                 G_warning(_("Writing area %d failed"), area);
                ret = -1;
                goto free_exit;
             }
         }
 #endif
             nskipped);
 
     /* free allocated space for isles */
free_exit:
     for (i = 0; i < nparts_alloc; i++)
         Vect_destroy_line_struct(Points[i]);
     Vect_destroy_cats_struct(Cats);
    G_free(Points);
 
    return ret;
 }
 
 /*!
 {
     int i, n, type;
     struct field_info *Fi;
    const char *map_name = NULL;
 
     n = Vect_get_num_dblinks(In);
 
                       In->dblnk->field[i].number);
             return -1;
         }
        if (field > 0 && Fi->number != field) {
            Vect_destroy_field_info(Fi);
             continue;
        }
 
         if (Vect_copy_table(In, Out, Fi->number, Fi->number, Fi->name, type) !=
             0) {
            map_name = Vect_get_full_name(In);
             G_warning(
                 _("Unable to copy table <%s> for layer %d from <%s> to <%s>"),
                Fi->table, Fi->number, map_name, Vect_get_name(Out));
            G_free((void *)map_name);
            Vect_destroy_field_info(Fi);
             return -1;
         }
        Vect_destroy_field_info(Fi);
     }
     return 0;
 }
 
                             int field_in, int field_out, const char *field_name,
                             int type, int *cats, int ncats)
 {
    int ret = 0;
     struct field_info *Fi, *Fin;
     const char *name, *key;
    dbDriver *driver = NULL;
 
     G_debug(2, "Vect_copy_table_by_cats(): field_in = %d field_out = %d",
             field_in, field_out);
     if (ret == -1) {
         G_warning(_("Unable to add database link for vector map <%s>"),
                   Out->name);
        goto free_exit;
     }
 
     if (cats)
                                 Fin->table, key, cats, ncats);
     if (ret == DB_FAILED) {
         G_warning(_("Unable to copy table <%s>"), Fin->table);
        ret = -1;
        goto free_exit;
     }
 
     driver = db_start_driver_open_database(Fin->driver,
     if (!driver) {
         G_warning(_("Unable to open database <%s> with driver <%s>"),
                   Fin->database, Fin->driver);
        ret = -1;
        goto free_exit;
     }
 
     /* do not allow duplicate keys */
     if (db_create_index2(driver, Fin->table, Fi->key) != DB_OK) {
         G_warning(_("Unable to create index"));
        ret = -1;
        goto close_db_free_exit;
     }
 
     if (db_grant_on_table(driver, Fin->table, DB_PRIV_SELECT,
                           DB_GROUP | DB_PUBLIC) != DB_OK) {
         G_warning(_("Unable to grant privileges on table <%s>"), Fin->table);
        ret = -1;
        goto close_db_free_exit;
     }
 
close_db_free_exit:
     db_close_database_shutdown_driver(driver);
 
free_exit:
    Vect_destroy_field_info(Fi);
    Vect_destroy_field_info(Fin);

    return ret;
 }