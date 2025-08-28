 	if (q_vector->rx.ring)
 		adapter->rx_ring[q_vector->rx.ring->queue_index] = NULL;
 
	if (!get_ecdev(adapter))
		netif_napi_del(&q_vector->napi);
 
 }
 
 		return -ENOMEM;
 
 	/* initialize NAPI */
	if (get_ecdev(adapter)) {
		netif_napi_add(adapter->netdev, &q_vector->napi,
				igb_poll, 64);
	}
 
 	/* tie q_vector and adapter together */
 	adapter->q_vector[v_idx] = q_vector;
 	bool clean_complete = true;
 	int work_done = 0;
 
 #ifdef CONFIG_IGB_DCA
 	if (q_vector->adapter->flags & IGB_FLAG_DCA_ENABLED)
 		igb_update_dca(q_vector);