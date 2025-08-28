 
     /* Query input maps */
     for (input = 0; input < 2; input++) {
        const char *mname = Vect_get_full_name(&(In[input]));
        G_message(_("Querying vector map <%s>..."), mname);
        G_free((void *)mname);
 
         nareas = Vect_get_num_areas(&(In[input]));
         G_percent(0, nareas, 1);
         if (centr[0] || centr[1])
             Vect_write_line(Out, GV_BOUNDARY, Points, Cats);
     }
    G_free(Centr);
    if (IPoints) {
        for (isle = 0; isle < nisles_alloc; isle++) {
            if (IPoints[isle])
                Vect_destroy_line_struct(IPoints[isle]);
        }
        G_free(IPoints);
    }
    Vect_destroy_line_struct(APoints);
 
     return 0;
 }