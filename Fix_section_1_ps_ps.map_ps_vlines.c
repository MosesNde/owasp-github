     }
     fprintf(PS.fp, "\n");
     fprintf(PS.fp, "0 setlinejoin\n"); /* reset line join to miter */
    Vect_destroy_line_struct(Points);
    Vect_destroy_line_struct(nPoints);
    Vect_destroy_cats_struct(Cats);
     return 0;
 }