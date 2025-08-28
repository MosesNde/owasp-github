     DCELL **rowbuf = (DCELL **)G_malloc(bands * sizeof(DCELL *));
     double **sum2 = (double **)G_calloc(bands, sizeof(double *));
     double *sumsq, *sd, *sum;
 
     if (stddev) {
         sumsq = (double *)G_calloc(bands, sizeof(double));
     }
     G_percent(1, 1, 1);
 
    if (count < 2)
        return 0;
 
     for (i = 0; i < bands; i++) {
         if (stddev) {
             if (j != i)
                 covar[j][i] = covar[i][j];
         }

        G_free(sum2[i]);
        G_free(rowbuf[i]);
     }
     for (i = 0; i < bands; i++)
         mu[i] = sum[i] / count;
 
     G_free(rowbuf);

     G_free(sum2);
    if (sd)
        G_free(sd);
    if (sumsq)
        G_free(sumsq);
 
    return 1;
 }
 
 static int write_pca(double **eigmat, double *mu, double *stddev, int *inp_fd,
     G_free(min);
     G_free(max);
     G_free(old_range);
 
     return 0;
 }