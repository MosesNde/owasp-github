 
     if (stat < 0) {
         Rast_unopen(rfd);
         return 1;
     }
 
     Rast_short_history(raster_map, "raster", &history);
     Rast_command_history(&history);
     Rast_write_history(raster_map, &history);
 
     return 0;
 }