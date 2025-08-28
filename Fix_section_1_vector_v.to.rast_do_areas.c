     CELL cat;
 
     G_begin_polygon_area_calculations();
 
     /* first count valid areas */
     nareas = Vect_get_num_areas(Map);
     if (nareas == 0)
         return 0;
 
    Cats = Vect_new_cats_struct();

     /* allocate list to hold valid area info */
     list = (struct list *)G_calloc(nareas * sizeof(char), sizeof(struct list));
 
         /* sort the list by size */
         qsort(list, nareas * sizeof(char), sizeof(struct list), compare);
     }
    Vect_destroy_cats_struct(Cats);
 
     return nareas_selected;
 }