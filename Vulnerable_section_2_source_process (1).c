  *
  * Copyright 2014 - 2016 ForgeRock AS.
  */
 
 #include "platform.h"
 #include "am.h"
     return out;
 }
 
 static am_return_t setup_request_data(am_request_t *r) {
     static const char *thisfunc = "setup_request_data():";
     am_status_t status = AM_ERROR, status_token_query = AM_ERROR;
         return AM_FAIL;
     }
 
     if (ISVALID(r->path_info) && r->conf->path_info_ignore) {
         r->overridden_url_pathinfo = remove_pathinfo_from_url(&request_url, r->path_info);
         if (r->overridden_url_pathinfo == NULL) {
 
     AM_LOG_DEBUG(r->instance_id, "%s \nmethod: %s \noriginal url: %s"
             "\nproto: %s\nhost: %s\nport: %d\npath: %s\nquery: %s\ncomplete: %s\noverridden: %s"
            "\npathinfo: %s"
             "\nnormalized (pathinfo removed): %s\noverridden (pathinfo removed): %s", thisfunc,
             am_method_num_to_str(r->method), r->orig_url,
             r->url.proto, r->url.host, r->url.port, r->url.path, r->url.query, r->normalized_url,
            r->overridden_url, LOGEMPTY(r->path_info),
             LOGEMPTY(r->normalized_url_pathinfo), LOGEMPTY(r->overridden_url_pathinfo));
 
     if (r->method == AM_REQUEST_POST && !ISVALID(r->content_type)) {
     if (map_sz > 0 && map != NULL) {
         am_config_map_t *m = (valid_idx >= map_sz) ? &map[0] : &map[valid_idx];
         if (add_goto_value) {
            char *goto_encoded = url_encode(r->overridden_url);
 
             if (r->conf->cdsso_enable &&
                     ISVALID(r->conf->url_redirect_param) &&
                     }
 
                 } else if (ISVALID(r->conf->access_denied_url)) {
                    char *goto_encoded = url_encode(r->overridden_url);
 
                     am_asprintf(&url, "%s%s%s=%s", r->conf->access_denied_url,
                             strchr(r->conf->access_denied_url, '?') == NULL ? "?" : "&",