 	data.data = malloc(1024); /* reasonable size initial buffer */
 	if(NULL == data.data) {
 		LM_ERR("NO MEMORY\n");
		curl_easy_cleanup(curl);
 		return -1;
 	}
 	memset(data.data, '\0', 1024);