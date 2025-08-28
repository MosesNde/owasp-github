         Vect_destroy_list(prev[i]);
     G_free(prev);
     graph_free(&g);
    Vect_destroy_line_struct(Points);
    Vect_destroy_cats_struct(Cats);
     return output;
 }