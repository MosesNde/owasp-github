 	const char *link;
 	struct request *req;
 	if (!(client && client->tab && client->tab->request)) return;
	req = client->tab->view;
	if (!req) req = client->tab->request;
 	ret = page_link_line(req->page,
 			req->scroll + ev.y - 1 - HAS_TABS(client), ev.x);
 	if (!ret) return;
 	ret--;
 	link = req->page.links[ret];
	ret = newtab ? client_newtab(client, link) :
 			tab_follow(client->tab, link);
 	if (ret) {
 		client->error = 1;
 	case TB_KEY_MOUSE_LEFT:
 	case TB_KEY_MOUSE_RIGHT:
 	case TB_KEY_MOUSE_MIDDLE:
 		if (ev.y == 0 && HAS_TABS(client)) {
 			return click_tab(client, ev,
 					ev.key == TB_KEY_MOUSE_MIDDLE);