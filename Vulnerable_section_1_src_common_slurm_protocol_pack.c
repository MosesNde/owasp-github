 {
 	int i;
 	node_info_msg_t *tmp_ptr;
 
 	xassert(msg);
 	tmp_ptr = xmalloc(sizeof(node_info_msg_t));
 	*msg = tmp_ptr;
 
 	/* load buffer's header (data structure version and time) */
 	if (protocol_version >= SLURM_24_11_PROTOCOL_VERSION) {
		bitstr_t *hidden_nodes = NULL;

 		safe_unpack32(&tmp_ptr->record_count, buffer);
 		safe_unpack_time(&tmp_ptr->last_update, buffer);
 		unpack_bit_str_hex(&hidden_nodes, buffer);
 	return SLURM_SUCCESS;
 
 unpack_error:
 	slurm_free_node_info_msg(tmp_ptr);
 	*msg = NULL;
 	return SLURM_ERROR;