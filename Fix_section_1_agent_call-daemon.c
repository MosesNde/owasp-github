             }
         }
 
      if (g->primary_ctx_reusable)
        assuan_release (g->primary_ctx);

       g->primary_ctx = NULL;
       g->primary_ctx_reusable = 0;
 