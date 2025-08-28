             next_node = n2; /* continue at end node */
         }
         else {
            if (cats_tmp)
                Vect_destroy_cats_struct(cats_tmp);
             return 1; /* no other line */
         }
     }