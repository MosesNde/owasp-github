             Vect_write_line(Out, ltype, Points, OCats);
         }
     }
    Vect_destroy_cats_struct(ACats);
    Vect_destroy_cats_struct(Cats);
    Vect_destroy_cats_struct(OCats);
    Vect_destroy_line_struct(Points);
 
     return 0;
 }