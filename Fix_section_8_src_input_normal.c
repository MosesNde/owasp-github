 int client_input_normal(struct client *client, struct tb_event ev) {
 	switch (ev.key) {
 	case TB_KEY_ESC:
		client_reset(client);
 		break;
 	case TB_KEY_MOUSE_WHEEL_DOWN:
 		if (!config.enableMouse) break;
 		break;
 	case TB_KEY_CTRL_Q:
 		if (!HAS_TABS(client)) return 1;
		STRLCPY(client->cmd, "Press 'y' to exit.");
 		client->exit = 1;
 		break;
 	case TB_KEY_CTRL_W:
 		return client_closetab(client);
	case TB_KEY_CTRL_T:
		return client_newtab(client, NULL, 0);
 	case TB_KEY_ENTER:
 		ev.ch = 'j';
 		break;
 				break;
 			}
 			if (ev.key == TB_KEY_BACK_TAB) {
				client_newtab(client, url, 0);
 				break;
 			}
 			ret = tab_request(client->tab, url);
 		}
 		break;
 	case 'b':
		client_newtab(client, "about:bookmarks", 0);
 		break;
 	case 'f':
		client_newtab(client, "about:history", 0);
 		break;
 	case 'y':
 		if (client->exit) return 1;