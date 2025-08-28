                                                       UINT16 responseType, UINT16 sequenceNumber)
 {
 	BOOL success = TRUE;
 	UINT64 timeDelta = GetTickCount64();
 
 	WINPR_ASSERT(autodetect);
 		timeDelta -= autodetect->bandwidthMeasureStartTime;
 
 	/* Send the result PDU to the server */
	wStream* s = rdp_message_channel_pdu_init(autodetect->context->rdp);
 
 	if (!s)
 		return FALSE;
 	if (!success)
 	{
 		WLog_Print(autodetect->log, WLOG_ERROR, "ClientBandwidthMeasureResult failed");
		Stream_Release(s);
 		return FALSE;
 	}
 