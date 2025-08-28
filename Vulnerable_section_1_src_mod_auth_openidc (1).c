                                                 url);
                 oidc_error(r, "%s: %s", *err_str, *err_desc);
                 return FALSE;
 	}
 
 	/* validate the URL to prevent HTTP header splitting */