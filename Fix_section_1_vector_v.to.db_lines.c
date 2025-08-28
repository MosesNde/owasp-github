         }
         G_percent(line_num, nlines, 2);
     }
    Vect_destroy_line_struct(EndPoints);
    Vect_destroy_cats_struct(RCats);
    Vect_destroy_line_struct(Points);
    Vect_destroy_cats_struct(LCats);
    Vect_destroy_cats_struct(Cats);
 
     return 0;
 }