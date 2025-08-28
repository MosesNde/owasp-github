     static double smseg;
     int MINPTS;
     double pr;
    struct triple *point = NULL;
     struct triple skip_point;
     int m_skip, skip_index, j, k, segtest;
     double xx, yy /*, zz */;
             }
             else if (segtest == 1) {
                 if (params->matrix_create(params, data->points,
                                          data->n_points - 1, matrix,
                                          indx) < 0) {
                    G_free(point);
                     return -1;
                }
             }
             if (!params->cv) {
                 for (i = 0; i < data->n_points; i++)
         G_free(data->points);
         G_free(data);
     }
    G_free(point);
     return 1;
 }
 