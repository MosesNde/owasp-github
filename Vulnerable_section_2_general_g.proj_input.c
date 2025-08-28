 #else
     OSRExportToPrettyWkt(hSRS, &tmpwkt, FALSE);
 #endif
     projwkt = G_store(tmpwkt);
     CPLFree(tmpwkt);
     set_authnamecode(hSRS);