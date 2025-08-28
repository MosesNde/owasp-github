                                                 url);
                 oidc_error(r, "%s: %s", *err_str, *err_desc);
                 return FALSE;
        } else if ((uri.hostname == NULL) && (strstr(url, "/\\") == url)) {
                *err_str = apr_pstrdup(r->pool, "Malformed URL");
                *err_desc =
                                apr_psprintf(r->pool,
                                                "No hostname was parsed and starting with '/\\': %s",
                                                url);
                oidc_error(r, "%s: %s", *err_str, *err_desc);
                return FALSE;
 	}
 
 	/* validate the URL to prevent HTTP header splitting */