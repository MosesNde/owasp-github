     struct line_cats *Cats;
     struct ilist *list;
 
    Points = Vect_new_line_struct();
     Cats = Vect_new_cats_struct();
    list = Vect_new_list();
     r = seg->route;
 
     Vect_cat_set(Cats, 2, line_id);
         return;
     }
 
     for (i = 0; i < nnodes; i++)
         edges[i] = 0;
     for (i = 0; i < lines[r]->n_values; i++)