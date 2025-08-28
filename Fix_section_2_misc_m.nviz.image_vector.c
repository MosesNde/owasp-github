 
         surf_list = GS_get_surf_list(&nsurf);
         GS_set_att_const(surf_list[0], ATT_TRANSP, 255);
        G_free(surf_list);
     }
 
     nvects = 0;
         if (mapset == NULL) {
             G_fatal_error(_("Vector map <%s> not found"), vect->answers[i]);
         }
        char *mname = G_fully_qualified_name(vect->answers[i], mapset);
        id = Nviz_new_map_obj(map_obj_type, mname, 0.0, data);
        G_free(mname);
 
         /* set position */
         x = atof(position->answers[i * 3 + 0]);
  */
 int vlines_set_attrb(const struct GParams *params)
 {
    int i, layer = -1, color, width, flat, height;
     int *vect_list, nvects;
     int have_colors;
 
             flat = 0;
 
         /* style (mode -- use memory by default) */
        if (GV_set_style(vect_list[i], TRUE, color, width, flat) < 0) {
            G_free(vect_list);
             return 0;
        }
 
         /* check for vector color table */
         have_colors = Vect_read_colors(params->vlines->answers[i], "", &colors);
 
         if (have_colors || color_column || width_column)
             if (GV_set_style_thematic(vect_list[i], layer, color_column,
                                       width_column,
                                      have_colors ? &colors : NULL) < 0) {
                G_free(vect_list);
                 return 0;
            }
 
         /* height */
         height = atoi(params->vline_height->answers[i]);
         if (height > 0)
             GV_set_trans(vect_list[i], 0.0, 0.0, height);
     }
    G_free(vect_list);
 
     return 1;
 }
  */
 int vpoints_set_attrb(const struct GParams *params)
 {
    int i, have_colors;
     int *site_list, nsites;
     int marker, color, width;
     float size;
     site_list = GP_get_site_list(&nsites);
 
     for (i = 0; i < nsites; i++) {
        int layer = -1, with_z = 0;
         check_map(params, i, FALSE, &layer, &with_z);
 
         color = Nviz_color_from_str(params->vpoint_color->answers[i]);
                 GP_set_zmode(site_list[i], TRUE);
         }
 
        if (GP_set_style(site_list[i], color, width, size, marker) < 0) {
            G_free(site_list);
             return 0;
        }
 
         /* check for vector color table */
         have_colors =
             marker_column) {
             if (GP_set_style_thematic(site_list[i], layer, color_column,
                                       width_column, size_column, marker_column,
                                      have_colors ? &colors : NULL) < 0) {
                G_free(site_list);
                 return 0;
            }
         }
     }
    G_free(site_list);
 
     return 1;
 }
 
     Fi = NULL;
     driver = NULL;
    column = NULL;
 
     if (vlines) {
         map = params->vlines->answers[index];
 
             if (db_column_Ctype(driver, Fi->table, color) != DB_C_TYPE_STRING)
                 G_fatal_error(_("Data type of color column must be character"));
            db_free_column(column);
            column = NULL;
         }
         if (size) {
             db_get_column(driver, Fi->table, size, &column);
             type = db_column_Ctype(driver, Fi->table, size);
             if (type != DB_C_TYPE_INT && type != DB_C_TYPE_DOUBLE)
                 G_fatal_error(_("Data type of size column must be numeric"));
            db_free_column(column);
            column = NULL;
         }
         if (width) {
             db_get_column(driver, Fi->table, width, &column);
             type = db_column_Ctype(driver, Fi->table, width);
             if (type != DB_C_TYPE_INT && type != DB_C_TYPE_DOUBLE)
                 G_fatal_error(_("Data type of width column must be numeric"));
            db_free_column(column);
            column = NULL;
         }
         if (marker) {
             db_get_column(driver, Fi->table, marker, &column);
             if (db_column_Ctype(driver, Fi->table, marker) != DB_C_TYPE_STRING)
                 G_fatal_error(
                     _("Data type of marker column must be character"));
            db_free_column(column);
            column = NULL;
         }
 
         db_close_database_shutdown_driver(driver);
        Vect_destroy_field_info(Fi);
     }
 
     Vect_close(&Map);