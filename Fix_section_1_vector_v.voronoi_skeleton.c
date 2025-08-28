             Vect_merge_lines(&Out, GV_LINE, NULL, NULL);
     }
 
    if (thresh >= 0) {
        Vect_destroy_line_struct(Points);
        Vect_destroy_list(list);
         return 0;
    }
 
     for (node = 1; node <= Vect_get_num_nodes(&Out); node++) {
         if (!Vect_node_alive(&Out, node))
         else
             Vect_merge_lines(&Out, GV_LINE, NULL, NULL);
     }
    Vect_destroy_line_struct(Points);
    Vect_destroy_list(list);
 
     return 0;
 }
             ntied++;
         }
     }
    Vect_destroy_line_struct(Points);
    Vect_destroy_cats_struct(Cats);
    for (i = 0; i < isl_allocated; i++) {
        if (IPoints[i]) {
            Vect_destroy_line_struct(IPoints[i]);
        }
    }
    G_free(IPoints);
 
     return ntied;
 }