 /* DEPRECATED: datum transformation is handled by PROJ */
 void print_datuminfo(void)
 {
    char *datum = NULL, *params = NULL;
     struct gpj_datum dstruct;
     int validdatum = 0;
 
     if (validdatum > 0)
         GPJ_free_datum(&dstruct);
 
    G_free(datum);
    G_free(params);

     return;
 }
 
 /* print input projection information in PROJ format */
 void print_proj4(int dontprettify)
 {
    struct pj_info pjinfo = {0};
     char *i, *projstrmod;
     const char *projstr;
     const char *unfact;
         if (pj_get_kv(&pjinfo, projinfo, projunits) == -1)
             G_fatal_error(
                 _("Unable to convert projection information to PROJ format"));
        projstr = G_store(pjinfo.def);
 #if PROJ_VERSION_MAJOR >= 5
         proj_destroy(pjinfo.pj);
 #else
     }
     fputc('\n', stdout);
     G_free(projstrmod);
    G_free(pjinfo.srid);
    G_free(pjinfo.def);
    G_free((void *)projstr);
 
     return;
 }