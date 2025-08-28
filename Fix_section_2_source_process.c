  *
  * Copyright 2014 - 2016 ForgeRock AS.
  */
/**
 * Portions Copyrighted 2022 OGIS-RI Co., Ltd.
 */
 
 #include "platform.h"
 #include "am.h"
     return out;
 }
 
char *get_goto_url(const char *orig_url, struct url *url) {
    char org_path[AM_URI_SIZE + 1];
    char *goto_url = NULL;
    char *p, *q;

    memset(org_path, 0, sizeof(org_path));
    p = strstr(orig_url, "://");
    if (p != NULL) {
        p = strstr(p + 3, "/");
        if (p != NULL) {
            q = org_path;
            int l = sizeof(org_path) - 1;
            for (int i = 0; i < l; i++) {
                if (*p != '\0' && *p != '?' && *p != '#') {
                    *q++ = *p++;
                } else {
                    break;
                }
            }
        } else {
            org_path[0] = '/';
        }
    } else {
        return NULL;
    }

    am_asprintf(&goto_url, "%s://%s:%d%s%s", url->proto, url->host,
            url->port, org_path, url->query);
    if (goto_url == NULL) {
        return NULL;
    }

    return goto_url;
}

 static am_return_t setup_request_data(am_request_t *r) {
     static const char *thisfunc = "setup_request_data():";
     am_status_t status = AM_ERROR, status_token_query = AM_ERROR;
         return AM_FAIL;
     }
 
    r->goto_url = get_goto_url(r->orig_url, &request_url);
    if (r->goto_url == NULL) {
        AM_LOG_ERROR(r->instance_id, "%s failed to make goto_url", thisfunc);
        return AM_FAIL;
    }

     if (ISVALID(r->path_info) && r->conf->path_info_ignore) {
         r->overridden_url_pathinfo = remove_pathinfo_from_url(&request_url, r->path_info);
         if (r->overridden_url_pathinfo == NULL) {
 
     AM_LOG_DEBUG(r->instance_id, "%s \nmethod: %s \noriginal url: %s"
             "\nproto: %s\nhost: %s\nport: %d\npath: %s\nquery: %s\ncomplete: %s\noverridden: %s"
            "\ngoto_url: %s\npathinfo: %s"
             "\nnormalized (pathinfo removed): %s\noverridden (pathinfo removed): %s", thisfunc,
             am_method_num_to_str(r->method), r->orig_url,
             r->url.proto, r->url.host, r->url.port, r->url.path, r->url.query, r->normalized_url,
            r->overridden_url, r->goto_url, LOGEMPTY(r->path_info),
             LOGEMPTY(r->normalized_url_pathinfo), LOGEMPTY(r->overridden_url_pathinfo));
 
     if (r->method == AM_REQUEST_POST && !ISVALID(r->content_type)) {
     if (map_sz > 0 && map != NULL) {
         am_config_map_t *m = (valid_idx >= map_sz) ? &map[0] : &map[valid_idx];
         if (add_goto_value) {
            char *goto_encoded = url_encode(r->goto_url);
 
             if (r->conf->cdsso_enable &&
                     ISVALID(r->conf->url_redirect_param) &&
                     }
 
                 } else if (ISVALID(r->conf->access_denied_url)) {
                    char *goto_encoded = url_encode(r->goto_url);
 
                     am_asprintf(&url, "%s%s%s=%s", r->conf->access_denied_url,
                             strchr(r->conf->access_denied_url, '?') == NULL ? "?" : "&",