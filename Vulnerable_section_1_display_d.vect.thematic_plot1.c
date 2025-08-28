     double *x, *y;
     struct line_pnts *Points /* , *PPoints */;
     struct line_cats *Cats;
 
     /* double msize; */
     int x0, y0;
     while (1) {
         if (Vect_level(Map) >= 2) {
             line++;
            if (line > nlines)
                return 0;
             if (!Vect_line_alive(Map, line))
                 continue;
             ltype = Vect_read_line(Map, Points, Cats, line);
             switch (ltype) {
             case -1:
                 fprintf(stderr, _("\nERROR: vector map - can't read\n"));
                return -1;
             case -2: /* EOF */
                return 0;
             }
         }
 
         }
     }
 
    Vect_destroy_line_struct(Points);
     Vect_destroy_cats_struct(Cats);

    return 0; /* not reached */
 }