   if (req->method != WEBB_GET)
     return 404;
 
  char file[PATH_MAX];
  if (snprintf(file, PATH_MAX, "%s%s", WORK_DIR, req->uri) < 0)
     return 404;
 
   struct stat sb;