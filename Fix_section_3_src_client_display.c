 void client_display(struct client* client) {
 	if (!client) return;
 	tb_clear();
 	tab_display(client->tab, client);
 	client_draw(client);
 	tb_present();
 	for (i = 0; i < client->width; i++) 
 		tb_set_cell(i, client->height - 2, ' ', TB_REV);
 
	if (client->error || client->exit) {
 		int color = client->error == ERROR_INFO ? TB_GREEN : TB_RED;
		if (client->exit) color = TB_DEFAULT;
 		tb_print(0, client->height - 1, TB_WHITE, color, client->cmd);
 	}
 