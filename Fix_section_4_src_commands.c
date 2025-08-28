 	if (!client->tab || !len) return 0;
 	if (*ptr) url = ptr;
 
	if ((ret = client_newtab(client, url, 0))) {
 		client->error = 1;
 		error_string(ret, V(client->cmd));
 	}
 	int ret;
 	if (no_argument(client, args, len)) return 0;
 	if (!client->tab) return 0;
	if ((ret = client_newtab(client, "about:help", 0)) ||
 			(ret = bookmark_rewrite())) {
 		error_string(ret, V(client->cmd));
 		client->error = 1;