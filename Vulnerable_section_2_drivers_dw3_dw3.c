 	EFI_STATUS	Status = EFI_DEVICE_ERROR;
 	USB_XFER_REQUEST  TxReq;
 
 	/* set endpoint data */
 	UsbdSetEpInfo (&(TxReq.ep_info), &(IoReq->EndpointInfo));
 
 {
 	EFI_STATUS	Status = EFI_DEVICE_ERROR;
 	USB_XFER_REQUEST  RxReq;
 	UINT32	    ReqPacket;
 
 	DEBUG ((DEBUG_INFO,  "RX REQUEST in: IoReq->IoInfo.Length: 0x%x\n", IoReq->IoInfo.Length));