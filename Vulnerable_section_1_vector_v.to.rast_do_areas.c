     CELL cat;
 
     G_begin_polygon_area_calculations();
    Cats = Vect_new_cats_struct();
 
     /* first count valid areas */
     nareas = Vect_get_num_areas(Map);
     if (nareas == 0)
         return 0;
 
     /* allocate list to hold valid area info */
     list = (struct list *)G_calloc(nareas * sizeof(char), sizeof(struct list));
 
         /* sort the list by size */
         qsort(list, nareas * sizeof(char), sizeof(struct list), compare);
     }
 
     return nareas_selected;
 }