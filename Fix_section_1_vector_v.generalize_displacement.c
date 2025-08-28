     matrix_free(&fy);
     matrix_free(&dx_old);
     matrix_free(&dy_old);
    Vect_destroy_cats_struct(Cats);
    Vect_destroy_line_struct(Points);
 
     return 0;
 }