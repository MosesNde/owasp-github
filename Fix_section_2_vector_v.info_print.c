     }
 
     map_type = Vect_maptype(Map);
    const char *maptype_str = Vect_maptype_info(Map);
    char *finfo_lname = Vect_get_finfo_layer_name(Map);
    const char *geom_type = Vect_get_finfo_geometry_type(Map);
 
     char scale_tmp[18];
     snprintf(scale_tmp, 18, "1:%d", Vect_get_scale(Map));
         case PLAIN:
             break;
         case SHELL:
            fprintf(stdout, "format=%s,%s\n", maptype_str,
                     Vect_get_finfo_format_info(Map));
            fprintf(stdout, "ogr_layer=%s\n", finfo_lname);
             fprintf(stdout, "ogr_dsn=%s\n", Vect_get_finfo_dsn_name(Map));
            fprintf(stdout, "feature_type=%s\n", geom_type);
             break;
         case JSON:
            json_object_set_string(root_object, "format", maptype_str);
             json_object_set_string(root_object, "format-detail",
                                    Vect_get_finfo_format_info(Map));
            json_object_set_string(root_object, "ogr_layer", finfo_lname);
             json_object_set_string(root_object, "ogr_dsn",
                                    Vect_get_finfo_dsn_name(Map));
            json_object_set_string(root_object, "feature_type", geom_type);
             break;
         }
     }
     else if (map_type == GV_FORMAT_POSTGIS) {
         int topo_format;
        char *toposchema_name = NULL, *topogeom_column = NULL;
         const struct Format_info *finfo;
 
         finfo = Vect_get_finfo(Map);
         case PLAIN:
             break;
         case SHELL:
            fprintf(stdout, "format=%s,%s\n", maptype_str,
                     Vect_get_finfo_format_info(Map));
            fprintf(stdout, "pg_table=%s\n", finfo_lname);
             fprintf(stdout, "pg_dbname=%s\n", Vect_get_finfo_dsn_name(Map));
             fprintf(stdout, "geometry_column=%s\n", finfo->pg.geom_column);
            fprintf(stdout, "feature_type=%s\n", geom_type);
             break;
         case JSON:
            json_object_set_string(root_object, "format", maptype_str);
             json_object_set_string(root_object, "format-detail",
                                    Vect_get_finfo_format_info(Map));
            json_object_set_string(root_object, "pg_table", finfo_lname);
             json_object_set_string(root_object, "pg_dbname",
                                    Vect_get_finfo_dsn_name(Map));
             json_object_set_string(root_object, "geometry_column",
                                    finfo->pg.geom_column);
            json_object_set_string(root_object, "feature_type", geom_type);
             break;
         }
 
                 break;
             }
         }
        G_free(topogeom_column);
        G_free(toposchema_name);
     }
     else {
         switch (format) {
         case PLAIN:
             break;
         case SHELL:
            fprintf(stdout, "format=%s\n", maptype_str);
             break;
         case JSON:
            json_object_set_string(root_object, "format", maptype_str);
             break;
         }
     }
                     break;
                 }
             }
            Vect_destroy_field_info(fi);
         }
     }
 
         json_object_set_string(root_object, "comment", Vect_get_comment(Map));
         break;
     }
    G_free(finfo_lname);
    G_free((void *)maptype_str);
    G_free((void *)geom_type);
 }
 
 void print_info(struct Map_info *Map)
 
     time_ok = first_time_ok = second_time_ok = FALSE;
     map_type = Vect_maptype(Map);
    const char *maptype_str = Vect_maptype_info(Map);
    char *finfo_lname = Vect_get_finfo_layer_name(Map);
    const char *geom_type = Vect_get_finfo_geometry_type(Map);
 
     /* Check the Timestamp */
     time_ok = G_read_vector_timestamp(Vect_get_name(Map), NULL, "", &ts);
     divider('|');
 
     if (map_type == GV_FORMAT_OGR || map_type == GV_FORMAT_OGR_DIRECT) {
        G_saprintf(line, "%-17s%s (%s)", _("Map format:"), maptype_str,
                   Vect_get_finfo_format_info(Map));
         printline(line);
 
         /* for OGR format print also datasource and layer */
        G_saprintf(line, "%-17s%s", _("OGR layer:"), finfo_lname);
         printline(line);
         G_saprintf(line, "%-17s%s", _("OGR datasource:"),
                    Vect_get_finfo_dsn_name(Map));
         printline(line);
        G_saprintf(line, "%-17s%s", _("Feature type:"), geom_type);
         printline(line);
     }
     else if (map_type == GV_FORMAT_POSTGIS) {
         int topo_format;
        char *toposchema_name = NULL, *topogeom_column = NULL;
         int topo_geo_only;
 
         const struct Format_info *finfo;
 
         finfo = Vect_get_finfo(Map);
 
        G_saprintf(line, "%-17s%s (%s)", _("Map format:"), maptype_str,
                   Vect_get_finfo_format_info(Map));
         printline(line);
 
         /* for PostGIS format print also datasource and layer */
        G_saprintf(line, "%-17s%s", _("DB table:"), finfo_lname);
         printline(line);
         G_saprintf(line, "%-17s%s", _("DB name:"),
                    Vect_get_finfo_dsn_name(Map));
                    finfo->pg.geom_column);
         printline(line);
 
        G_saprintf(line, "%-17s%s", _("Feature type:"), geom_type);
         printline(line);
 
         topo_format = Vect_get_finfo_topology_info(
                        "pseudo (simple features)");
 
         printline(line);
        G_free(toposchema_name);
        G_free(topogeom_column);
     }
     else {
        G_saprintf(line, "%-17s%s", _("Map format:"), maptype_str);
         printline(line);
     }
 
     printline(line);
     divider('+');
     fprintf(stdout, "\n");
    G_free((void *)maptype_str);
    G_free(finfo_lname);
    G_free((void *)geom_type);
 }
 
 /*!