 	if (q_vector->rx.ring)
 		adapter->rx_ring[q_vector->rx.ring->queue_index] = NULL;
 
	netif_napi_del(&q_vector->napi);
 }
 
 static void igb_reset_interrupt_capability(struct igb_adapter *adapter)
 		return -ENOMEM;
 
 	/* initialize NAPI */
	netif_napi_add(adapter->netdev, &q_vector->napi,
			igb_poll, 64);
 
 	/* tie q_vector and adapter together */
 	adapter->q_vector[v_idx] = q_vector;
 	first->bytecount = skb->len;
 	first->gso_segs = 1;
 
	if (unlikely(!adapter->ecdev &&
 				skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP)) {
 
 		if (adapter->tstamp_config.tx_type == HWTSTAMP_TX_ON &&
 	bool clean_complete = true;
 	int work_done = 0;
 
	if (q_vector->adapter->ecdev) {
		return -EBUSY;
	}

 #ifdef CONFIG_IGB_DCA
 	if (q_vector->adapter->flags & IGB_FLAG_DCA_ENABLED)
 		igb_update_dca(q_vector);
 	q_vector->tx.total_bytes += total_bytes;
 	q_vector->tx.total_packets += total_packets;
 
	if (!adapter->ecdev &&
 			test_bit(IGB_RING_FLAG_TX_DETECT_HANG, &tx_ring->flags)) {
 		struct e1000_hw *hw = &adapter->hw;
 
 			total_packets++;
 			continue;
 		}

 		/* verify the packet layout is correct */
 		if (igb_cleanup_headers(rx_ring, rx_desc, skb)) {
 			skb = NULL;