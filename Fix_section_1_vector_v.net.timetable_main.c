     struct line_cats *Cats;
     struct ilist *list;
 
     Cats = Vect_new_cats_struct();
     r = seg->route;
 
     Vect_cat_set(Cats, 2, line_id);
         return;
     }
 
    Points = Vect_new_line_struct();
    list = Vect_new_list();

     for (i = 0; i < nnodes; i++)
         edges[i] = 0;
     for (i = 0; i < lines[r]->n_values; i++)