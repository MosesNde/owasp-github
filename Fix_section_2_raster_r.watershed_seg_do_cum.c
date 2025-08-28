     G_percent(do_points, do_points, 1); /* finish it */
 
     seg_close(&astar_pts);
    G_free(dist_to_nbr);
    G_free(contour);
 
     return 0;
 }