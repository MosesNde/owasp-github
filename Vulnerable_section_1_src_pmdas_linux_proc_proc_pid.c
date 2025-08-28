 }
 
 static void
accumulate_proc_fdinfo(proc_pid_entry_t *ep, proc_pid_fdinfo_t fdinfo)
 {
     /* Generic DRM data */
    ep->fdinfo.drm_memory_cpu += fdinfo.drm_memory_cpu;
    ep->fdinfo.drm_memory_gtt += fdinfo.drm_memory_gtt;
    ep->fdinfo.drm_memory_vram += fdinfo.drm_memory_vram;
    ep->fdinfo.drm_shared_cpu += fdinfo.drm_shared_cpu;
    ep->fdinfo.drm_shared_gtt += fdinfo.drm_shared_gtt;
    ep->fdinfo.drm_shared_vram += fdinfo.drm_shared_vram;
     /* AMD GPU specific data */
    ep->fdinfo.amd_evicted_visible_vram += fdinfo.amd_evicted_visible_vram;
    ep->fdinfo.amd_evicted_vram += fdinfo.amd_evicted_vram;
    ep->fdinfo.amd_memory_visible_vram += fdinfo.amd_memory_visible_vram;
    ep->fdinfo.amd_requested_gtt += fdinfo.amd_requested_gtt;
    ep->fdinfo.amd_requested_visible_vram += fdinfo.amd_requested_visible_vram;
    ep->fdinfo.amd_requested_vram += fdinfo.amd_requested_vram;
 }
 
 static int
 	if (!duplicate)
 	    fdinfos[fd_it++] = fdinfo;
     }
    closedir(dirp);
 
     /* Reset any previous data, before accumulation.
      * If we wanted to keep all infos separated, we could simply
     memset(&ep->fdinfo, 0, sizeof(ep->fdinfo));
 
     for (int i = 0; i < fd_it; i++)
	accumulate_proc_fdinfo(ep, fdinfos[i]);
 
     ep->success |= PROC_PID_FLAG_FDINFO;
     free(fdinfos);
 
     if (sts < 0 && pmDebugOptions.appl1)
 	fprintf(stderr, "refresh_proc_pid_fdinfo(pid=%d) -> %d\n", ep->id, sts);