 static int session_active_segs_isempty(session_t* session);
 static int request_validate(request_t *r);
 static int request_set_path(request_t *r, const char* d, char* p, char* pp, char* path);
 static int request_parse_gp_headers(request_t *r, int opt_g);
 static void free_session_cb(int fd, short event, void* arg);
 #ifdef GPFXDIST
 	/* decode %xx to char */
 	percent_encoding_to_char(p, pp, path);
 
 	/*
 	 * This is a debug hook. We'll get here By creating an external table with
 	 * name(a text) location('gpfdist://<host>:<port>/gpfdist/status').
 
 static int request_set_path(request_t *r, const char* d, char* p, char* pp, char* path)
 {

	/*
	 * disallow using a relative path in the request
	 */
	if (strstr(path, ".."))
	{
		gwarning(r, "reject invalid request from %s [%s %s] - request "
						"is using a relative path",
						r->peer,
						r->in.req->argv[0],
						r->in.req->argv[1]);

		http_error(r, FDIST_BAD_REQUEST, "invalid request due to relative path");
		request_end(r, 1, 0);

		return -1;
	}

 	r->path = 0;
 
 	/*
 	return 0;
 }
 
 static int request_validate(request_t *r)
 {
 	/* parse the HTTP request. Expect "GET /path HTTP/1.X" or "PUT /path HTTP/1.X" */