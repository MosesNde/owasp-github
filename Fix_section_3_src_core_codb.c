         ds301 = NULL;
     }
 
    if (init_th != NULL)
    {
        os_detach_thread(init_th);
        init_th = NULL;
    }

     unload_codb();
 }
 