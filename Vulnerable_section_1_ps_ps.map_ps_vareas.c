     if (0 > (ret = Vect_get_area_points(P_map, area, Points))) {
         if (ret == -1)
             G_warning(_("Read error in vector map"));
         return 0;
     }
     construct_path(Points, shift, WHOLE_PATH);
         if (0 > (ret = Vect_get_isle_points(P_map, island, Points))) {
             if (ret == -1)
                 G_warning(_("Read error in vector map"));
             return -1;
         }
         construct_path(Points, shift, WHOLE_PATH);
     }
     return 1;
 }
 