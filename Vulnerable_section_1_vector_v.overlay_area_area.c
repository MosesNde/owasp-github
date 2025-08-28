 
     /* Query input maps */
     for (input = 0; input < 2; input++) {
        G_message(_("Querying vector map <%s>..."),
                  Vect_get_full_name(&(In[input])));
 
         nareas = Vect_get_num_areas(&(In[input]));
         G_percent(0, nareas, 1);
         if (centr[0] || centr[1])
             Vect_write_line(Out, GV_BOUNDARY, Points, Cats);
     }
 
     return 0;
 }