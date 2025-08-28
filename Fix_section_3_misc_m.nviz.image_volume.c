             G_fatal_error(_("3d raster map <%s> not found"),
                           params->volume->answers[i]);
         }
        char *mname =
            G_fully_qualified_name(params->volume->answers[i], mapset);
        id = Nviz_new_map_obj(MAP_OBJ_VOL, mname, 0.0, data);
        G_free(mname);
 
         /* set position */
         if (opt_get_num_answers(params->volume_pos) != 3 * nvol) {
 
         GVL_isosurf_set_drawmode(id, draw_mode);
     }
    G_free(vol_list);
 
     return 1;
 }
 
         GVL_slice_set_drawmode(id, draw_mode);
     }
    G_free(vol_list);
 
     return 1;
 }