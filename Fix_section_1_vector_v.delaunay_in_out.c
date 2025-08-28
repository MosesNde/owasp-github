             e = NEXT(e, u);
         } while (!SAME_EDGE(e, e_start));
     }
    Vect_destroy_line_struct(Points);
    Vect_destroy_cats_struct(Cats);
 }
 
 void remove_duplicates(unsigned int *size)