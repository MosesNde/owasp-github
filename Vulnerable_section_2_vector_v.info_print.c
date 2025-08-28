     }
 
     map_type = Vect_maptype(Map);
 
     char scale_tmp[18];
     snprintf(scale_tmp, 18, "1:%d", Vect_get_scale(Map));
         case PLAIN:
             break;
         case SHELL:
            fprintf(stdout, "format=%s,%s\n", Vect_maptype_info(Map),
                     Vect_get_finfo_format_info(Map));
            fprintf(stdout, "ogr_layer=%s\n", Vect_get_finfo_layer_name(Map));
             fprintf(stdout, "ogr_dsn=%s\n", Vect_get_finfo_dsn_name(Map));
            fprintf(stdout, "feature_type=%s\n",
                    Vect_get_finfo_geometry_type(Map));
             break;
         case JSON:
            json_object_set_string(root_object, "format",
                                   Vect_maptype_info(Map));
             json_object_set_string(root_object, "format-detail",
                                    Vect_get_finfo_format_info(Map));
            json_object_set_string(root_object, "ogr_layer",
                                   Vect_get_finfo_layer_name(Map));
             json_object_set_string(root_object, "ogr_dsn",
                                    Vect_get_finfo_dsn_name(Map));
            json_object_set_string(root_object, "feature_type",
                                   Vect_get_finfo_geometry_type(Map));
             break;
         }
     }
     else if (map_type == GV_FORMAT_POSTGIS) {
         int topo_format;
        char *toposchema_name, *topogeom_column;
         const struct Format_info *finfo;
 
         finfo = Vect_get_finfo(Map);
         case PLAIN:
             break;
         case SHELL:
            fprintf(stdout, "format=%s,%s\n", Vect_maptype_info(Map),
                     Vect_get_finfo_format_info(Map));
            fprintf(stdout, "pg_table=%s\n", Vect_get_finfo_layer_name(Map));
             fprintf(stdout, "pg_dbname=%s\n", Vect_get_finfo_dsn_name(Map));
             fprintf(stdout, "geometry_column=%s\n", finfo->pg.geom_column);
            fprintf(stdout, "feature_type=%s\n",
                    Vect_get_finfo_geometry_type(Map));
             break;
         case JSON:
            json_object_set_string(root_object, "format",
                                   Vect_maptype_info(Map));
             json_object_set_string(root_object, "format-detail",
                                    Vect_get_finfo_format_info(Map));
            json_object_set_string(root_object, "pg_table",
                                   Vect_get_finfo_layer_name(Map));
             json_object_set_string(root_object, "pg_dbname",
                                    Vect_get_finfo_dsn_name(Map));
             json_object_set_string(root_object, "geometry_column",
                                    finfo->pg.geom_column);
            json_object_set_string(root_object, "feature_type",
                                   Vect_get_finfo_geometry_type(Map));
             break;
         }
 
                 break;
             }
         }
     }
     else {
         switch (format) {
         case PLAIN:
             break;
         case SHELL:
            fprintf(stdout, "format=%s\n", Vect_maptype_info(Map));
             break;
         case JSON:
            json_object_set_string(root_object, "format",
                                   Vect_maptype_info(Map));
             break;
         }
     }
                     break;
                 }
             }
         }
     }
 
         json_object_set_string(root_object, "comment", Vect_get_comment(Map));
         break;
     }
 }
 
 void print_info(struct Map_info *Map)
 
     time_ok = first_time_ok = second_time_ok = FALSE;
     map_type = Vect_maptype(Map);
 
     /* Check the Timestamp */
     time_ok = G_read_vector_timestamp(Vect_get_name(Map), NULL, "", &ts);
     divider('|');
 
     if (map_type == GV_FORMAT_OGR || map_type == GV_FORMAT_OGR_DIRECT) {
        G_saprintf(line, "%-17s%s (%s)", _("Map format:"),
                   Vect_maptype_info(Map), Vect_get_finfo_format_info(Map));
         printline(line);
 
         /* for OGR format print also datasource and layer */
        G_saprintf(line, "%-17s%s", _("OGR layer:"),
                   Vect_get_finfo_layer_name(Map));
         printline(line);
         G_saprintf(line, "%-17s%s", _("OGR datasource:"),
                    Vect_get_finfo_dsn_name(Map));
         printline(line);
        G_saprintf(line, "%-17s%s", _("Feature type:"),
                   Vect_get_finfo_geometry_type(Map));
         printline(line);
     }
     else if (map_type == GV_FORMAT_POSTGIS) {
         int topo_format;
        char *toposchema_name, *topogeom_column;
         int topo_geo_only;
 
         const struct Format_info *finfo;
 
         finfo = Vect_get_finfo(Map);
 
        G_saprintf(line, "%-17s%s (%s)", _("Map format:"),
                   Vect_maptype_info(Map), Vect_get_finfo_format_info(Map));
         printline(line);
 
         /* for PostGIS format print also datasource and layer */
        G_saprintf(line, "%-17s%s", _("DB table:"),
                   Vect_get_finfo_layer_name(Map));
         printline(line);
         G_saprintf(line, "%-17s%s", _("DB name:"),
                    Vect_get_finfo_dsn_name(Map));
                    finfo->pg.geom_column);
         printline(line);
 
        G_saprintf(line, "%-17s%s", _("Feature type:"),
                   Vect_get_finfo_geometry_type(Map));
         printline(line);
 
         topo_format = Vect_get_finfo_topology_info(
                        "pseudo (simple features)");
 
         printline(line);
     }
     else {
        G_saprintf(line, "%-17s%s", _("Map format:"), Vect_maptype_info(Map));
         printline(line);
     }
 
     printline(line);
     divider('+');
     fprintf(stdout, "\n");
 }
 
 /*!