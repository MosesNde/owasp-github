             if (a < 0) {
                 G_warning(_("Can't insert %lf,%lf,%lf,%lf,%lf a=%d"), x, y, z,
                           w, sm, a);
                Vect_destroy_field_info(Fi);
                 return -1;
             }
 
         }
         else {
             fprintf(stderr, "ERROR: zero points in the given region!\n");
            Vect_destroy_field_info(Fi);
             return -1;
         }
     }
                 KMIN, KMAX);
         fprintf(stderr, "for smooth connection of segments, npmin > segmax "
                         "(see manual) \n");
        Vect_destroy_field_info(Fi);
         return -1;
     }
 
         }
         G_message(_("Bitmap mask created"));
     }
    Vect_destroy_field_info(Fi);
 
     return 1;
 }