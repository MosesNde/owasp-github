         G_free_tokens(tokens);
     }
     G_percent(nrows, nrows, 2);
    Vect_destroy_line_struct(Points);
    Vect_destroy_cats_struct(Cats);
    G_free(buf);
 
     return 0;
 }