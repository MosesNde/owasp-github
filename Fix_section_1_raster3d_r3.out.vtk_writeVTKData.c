         fprintf(fp, "POINT_DATA %i\n",
                 region.cols * region.rows *
                     region.depths); /*We have pointdata */
    G_free(rast_top);
    G_free(rast_bottom);
     return;
 }
 