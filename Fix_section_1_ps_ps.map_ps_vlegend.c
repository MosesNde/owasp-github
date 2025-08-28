     if (PS.min_y > y)
         PS.min_y = y;
 
    G_free(nvec);
    for (i = 0; i < vector.count; i++)
        G_free(vec[i]);
    G_free(vec);
     return 0;
 }