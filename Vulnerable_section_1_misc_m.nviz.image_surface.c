  */
 int load_rasters(const struct GParams *params, nv_data *data)
 {
    const char *mapset;
     int i;
     int nelevs, nelev_map, nelev_const, ncolor_map, ncolor_const, nmask_map;
     int ntransp_map, ntransp_const, nshine_map, nshine_const;
                 G_fatal_error(_("Raster map <%s> not found"),
                               params->elev_map->answers[i]);
             }

            id = Nviz_new_map_obj(
                MAP_OBJ_SURF,
                G_fully_qualified_name(params->elev_map->answers[i], mapset),
                0.0, data);
         }
         else {
             if (i - nelev_map < nelev_const &&
                 G_fatal_error(_("Raster map <%s> not found"),
                               params->color_map->answers[i]);
             }
            Nviz_set_attr(
                id, MAP_OBJ_SURF, ATT_COLOR, MAP_ATT,
                G_fully_qualified_name(params->color_map->answers[i], mapset),
                -1.0, data);
         }
         /* check for color value */
         else if (i - ncolor_map < ncolor_const &&
         }
         else { /* use by default elevation map for coloring */
             if (nelev_map > 0) {
                Nviz_set_attr(id, MAP_OBJ_SURF, ATT_COLOR, MAP_ATT,
                              G_fully_qualified_name(
                                  params->elev_map->answers[i], mapset),
                              -1.0, data);
                 G_verbose_message(
                     _("Color attribute not defined, using default <%s>"),
                    G_fully_qualified_name(params->elev_map->answers[i],
                                           mapset));
             }
             else {
                 G_fatal_error(_("Missing color attribute for surface %d"),
         }
         /* mask */
         if (i < nmask_map && strcmp(params->mask_map->answers[i], "")) {
            Nviz_set_attr(
                id, MAP_OBJ_SURF, ATT_MASK, MAP_ATT,
                G_fully_qualified_name(params->mask_map->answers[i], mapset),
                -1.0, data);
         }
 
         /* transparency */
         if (i < ntransp_map && strcmp(params->transp_map->answers[i], "")) {
            Nviz_set_attr(
                id, MAP_OBJ_SURF, ATT_TRANSP, MAP_ATT,
                G_fully_qualified_name(params->transp_map->answers[i], mapset),
                -1.0, data);
         }
         else if (i - ntransp_map < ntransp_const &&
                  strcmp(params->transp_const->answers[i - ntransp_map], "")) {
 
         /* shininess */
         if (i < nshine_map && strcmp(params->shine_map->answers[i], "")) {
            Nviz_set_attr(
                id, MAP_OBJ_SURF, ATT_SHINE, MAP_ATT,
                G_fully_qualified_name(params->shine_map->answers[i], mapset),
                -1.0, data);
         }
         else if (i - nshine_map < nshine_const &&
                  strcmp(params->shine_const->answers[i - nshine_map], "")) {
 
         /* emission */
         if (i < nemit_map && strcmp(params->emit_map->answers[i], "")) {
            Nviz_set_attr(
                id, MAP_OBJ_SURF, ATT_EMIT, MAP_ATT,
                G_fully_qualified_name(params->emit_map->answers[i], mapset),
                -1.0, data);
         }
         else if (i - nemit_map < nemit_const &&
                  strcmp(params->emit_const->answers[i - nemit_map], "")) {
            set_default_wirecolors(data, i);
          */
     }
 
     return nsurfs;
 }
         /* wire color */
         GS_set_wire_color(id, Nviz_color_from_str(wire_color));
     }
 
     return;
 }