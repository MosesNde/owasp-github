 
     res = hev_logger_init (log_level, log_file);
     if (res < 0)
        return -2;
 
     res = hev_socks5_logger_init (log_level, log_file);
     if (res < 0)
        return -3;
 
     nofile = hev_config_get_misc_limit_nofile ();
     res = set_limit_nofile (nofile);
 
     res = hev_socks5_proxy_init ();
     if (res < 0)
        return -4;
 
     hev_socks5_proxy_run ();
 
     hev_socks5_proxy_fini ();
     hev_socks5_logger_fini ();
     hev_logger_fini ();
     hev_config_fini ();

    return 0;
 }
 
 int