 	if (!tab) return 0;
 	format_link(link, MAX_URL, V(buf));
 	if (!(req = tab_completed(tab))) return 0;
	if ((ret = request_follow(tab->request, buf, V(url)))) return ret;
 	tab_request(tab, url);
 
 	return 0;