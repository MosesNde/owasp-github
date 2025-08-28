         ESP_LOGE(TAG, "Unable to allocate httpd send buffer");
         return ESP_ERR_HTTPD_ALLOC_MEM;
     }
    ESP_LOGD(TAG, "httpd send buffer size = %d", strlen(res_buf));
 
     esp_err_t ret = snprintf(res_buf, required_size, httpd_hdr_str, ra->status, ra->content_type, buf_len);
     if (ret < 0 || ret >= required_size) {
         free(res_buf);
         return ESP_ERR_HTTPD_RESP_HDR;
     }
     ret = httpd_send_all(r, res_buf, strlen(res_buf));
     free(res_buf);
     if (ret != ESP_OK) {
     /* Request headers are no longer available */
     ra->req_hdrs_count = 0;
 
    /* Calculate the size of the headers. +1 for the null terminator */
    size_t required_size = snprintf(NULL, 0, httpd_chunked_hdr_str, ra->status, ra->content_type) + 1;
    if (required_size > ra->max_req_hdr_len) {
        return ESP_ERR_HTTPD_RESP_HDR;
    }
    char *res_buf = malloc(required_size); /* Temporary buffer to store the headers */
    if (res_buf == NULL) {
        ESP_LOGE(TAG, "Unable to allocate httpd send chunk buffer");
        return ESP_ERR_HTTPD_ALLOC_MEM;
    }
    ESP_LOGD(TAG, "httpd send chunk buffer size = %d", strlen(res_buf));
     if (!ra->first_chunk_sent) {
         esp_err_t ret = snprintf(res_buf, required_size, httpd_chunked_hdr_str, ra->status, ra->content_type);
         if (ret < 0 || ret >= required_size) {
             free(res_buf);
             return ESP_ERR_HTTPD_RESP_HDR;
         }
         /* Size of essential headers is limited by scratch buffer size */
         ret = httpd_send_all(r, res_buf, strlen(res_buf));
         free(res_buf);