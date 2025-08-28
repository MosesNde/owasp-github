  *
  * Copyright 2014 - 2016 ForgeRock AS.
  */
 
 #include "platform.h"
 #include "am.h"
         }
     }
 
    d = strdup(url->path);
     if (d == NULL) {
         url->error = AM_ENOMEM;
         return AM_ERROR;
 void am_request_free(am_request_t *r) {
     if (r != NULL) {
         AM_FREE(r->normalized_url, r->overridden_url, r->normalized_url_pathinfo,
                r->overridden_url_pathinfo, r->token,
                 r->client_ip, r->client_host, r->post_data, r->post_data_fn,
                 r->session_info.s1, r->session_info.si, r->session_info.sk);
         delete_am_policy_result_list(&r->pattr);