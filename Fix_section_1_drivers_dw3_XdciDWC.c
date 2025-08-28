 	USB_XFER_REQUEST     *xfer_req;
 	UINT32               remaining_len;
 
	if (ep_num >= DWC_XDCI_MAX_ENDPOINTS) {
		ep_num = DWC_XDCI_MAX_ENDPOINTS - 1;
 	}
 
 	if (core_handle == NULL) {