 	return client->tab == NULL;
 }
 
int client_newtab(struct client *client, const char *url, int follow) {
 	struct tab *tab;
 	int proto;
 	if (!url) url = "about:newtab";
 		if (tab->next) tab->next->prev = tab;
 		tab->prev = client->tab;
 		client->tab->next = tab;
		if (follow && client->tab->request && proto == PROTOCOL_NONE) {
 			struct request req = {0};
 			STRLCPY(req.url, client->tab->request->url);
 			request_follow(&req, url, V(req.url));