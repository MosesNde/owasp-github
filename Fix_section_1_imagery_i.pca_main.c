     DCELL **rowbuf = (DCELL **)G_malloc(bands * sizeof(DCELL *));
     double **sum2 = (double **)G_calloc(bands, sizeof(double *));
     double *sumsq, *sd, *sum;
    int ret = 1;
 
     if (stddev) {
         sumsq = (double *)G_calloc(bands, sizeof(double));
     }
     G_percent(1, 1, 1);
 
    if (count < 2) {
        ret = 0;
        goto free_exit;
    }
 
     for (i = 0; i < bands; i++) {
         if (stddev) {
             if (j != i)
                 covar[j][i] = covar[i][j];
         }
     }
     for (i = 0; i < bands; i++)
         mu[i] = sum[i] / count;
 
free_exit:
    for (i = 0; i < bands; i++) {
        G_free(sum2[i]);
        G_free(rowbuf[i]);
    }
     G_free(rowbuf);
     G_free(sum2);
    G_free(sd);
    G_free(sumsq);
 
    return ret;
 }
 
 static int write_pca(double **eigmat, double *mu, double *stddev, int *inp_fd,
     G_free(min);
     G_free(max);
     G_free(old_range);
    G_free(pcs);
    G_free(out_fd);
 
     return 0;
 }