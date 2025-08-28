 #include "tab.h"
 #include "error.h"
 #include "parser.h"
 
 static void insert_unicode(char *buf, size_t length, int *pos, uint32_t ch) {
 	char cpy[MAX_CMDLINE];
 
 	switch (ev.key) {
 	case TB_KEY_ESC:
 		client->mode = MODE_NORMAL;
 		if (req) req->state = STATE_ENDED;
 		return 0;