 #else
     OSRExportToPrettyWkt(hSRS, &tmpwkt, FALSE);
 #endif
    G_free(projwkt);
     projwkt = G_store(tmpwkt);
     CPLFree(tmpwkt);
     set_authnamecode(hSRS);