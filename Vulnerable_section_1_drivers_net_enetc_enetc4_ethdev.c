 	uint32_t i = 0;
 
 	hw->txq_prior = rte_zmalloc(NULL, hw->max_tx_queues * sizeof(uint32_t), 0);
 	str = strtok(input_str, "|");
 	while (str != NULL && i < hw->max_tx_queues) {
 		hw->txq_prior[i++] = atoi(str);
 		str = strtok(NULL, "|");
 	}
 
 	return 0;
 }
 