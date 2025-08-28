 
     res = hev_logger_init (log_level, log_file);
     if (res < 0)
        goto exit1;
 
     res = hev_socks5_logger_init (log_level, log_file);
     if (res < 0)
        goto exit2;
 
     nofile = hev_config_get_misc_limit_nofile ();
     res = set_limit_nofile (nofile);
 
     res = hev_socks5_proxy_init ();
     if (res < 0)
        goto exit3;
 
     hev_socks5_proxy_run ();
 
     hev_socks5_proxy_fini ();
exit3:
     hev_socks5_logger_fini ();
exit2:
     hev_logger_fini ();
exit1:
     hev_config_fini ();
    return res;
 }
 
 int