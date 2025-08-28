 
 BOOL rdp_send_client_control_pdu(rdpRdp* rdp, UINT16 action)
 {
 	UINT16 GrantId = 0;
 	UINT16 ControlId = 0;
 
 			return FALSE;
 	}
 
	wStream* s = rdp_data_pdu_init(rdp);
 	if (!s)
 		return FALSE;
 	if (!rdp_write_client_control_pdu(s, action, GrantId, ControlId))