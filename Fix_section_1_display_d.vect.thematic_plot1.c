     double *x, *y;
     struct line_pnts *Points /* , *PPoints */;
     struct line_cats *Cats;
    int ret = 0;
 
     /* double msize; */
     int x0, y0;
     while (1) {
         if (Vect_level(Map) >= 2) {
             line++;
            if (line > nlines) {
                ret = 0;
                goto cleanup_and_exit;
            }
             if (!Vect_line_alive(Map, line))
                 continue;
             ltype = Vect_read_line(Map, Points, Cats, line);
             switch (ltype) {
             case -1:
                 fprintf(stderr, _("\nERROR: vector map - can't read\n"));
                ret = -1;
                goto cleanup_and_exit;
             case -2: /* EOF */
                ret = 0;
                goto cleanup_and_exit;
             }
         }
 
         }
     }
 
cleanup_and_exit:
    G_free(primary_color);
    G_free(fill_color);
    G_free(line_color);
     Vect_destroy_cats_struct(Cats);
    Vect_destroy_line_struct(Points);
    return ret;
 }