 int Nviz_get_exag_height(double *val, double *min, double *max)
 {
     float longdim, exag, texag, hmin, hmax, fmin, fmax;
    int nsurfs, i, *surf_list;
 
     surf_list = GS_get_surf_list(&nsurfs);
     if (nsurfs) {
 
     G_debug(1, "Nviz_get_exag_height(): value = %f min = %f max = %f", *val,
             min ? *min : 0.0, max ? *max : 0.0);
 
     return 1;
 }
 double Nviz_get_exag(void)
 {
     float exag, texag;
    int nsurfs, i, *surf_list;
 
     surf_list = GS_get_surf_list(&nsurfs);
 
 
     if (exag == 0.0)
         exag = 1.0;

    if (nsurfs > 0)
        G_free(surf_list);
 
     G_debug(1, "Nviz_get_exag(): value = %f", exag);
     return exag;