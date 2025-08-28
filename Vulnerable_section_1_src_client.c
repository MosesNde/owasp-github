 			unsupported_protocol_extensions.write_pos
 			);
 		res = pktbuf_send_immediate(buf, client);
		if (!res)
 			disconnect_client(client, false, "unable to send protocol negotiation packet");
 	}
 
 	/* find pool */