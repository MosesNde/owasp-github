 		return 0;
 }
 
 static int
 dpaa2_dev_info_get(struct rte_eth_dev *dev,
 	struct rte_eth_dev_info *dev_info)
 					dev_rx_offloads_nodis;
 	dev_info->tx_offload_capa = dev_tx_offloads_sup |
 					dev_tx_offloads_nodis;
	dev_info->speed_capa = RTE_ETH_LINK_SPEED_1G |
			RTE_ETH_LINK_SPEED_2_5G |
			RTE_ETH_LINK_SPEED_10G;
 	dev_info->dev_capa &= ~RTE_ETH_DEV_CAPA_FLOW_RULE_KEEP;
 
 	dev_info->max_hash_mac_addrs = 0;
 	dev_info->default_txportconf.ring_size = CONG_ENTER_TX_THRESHOLD;
 	dev_info->default_rxportconf.ring_size = DPAA2_RX_DEFAULT_NBDESC;
 
	if (dpaa2_svr_family == SVR_LX2160A) {
		dev_info->speed_capa |= RTE_ETH_LINK_SPEED_25G |
				RTE_ETH_LINK_SPEED_40G |
				RTE_ETH_LINK_SPEED_50G |
				RTE_ETH_LINK_SPEED_100G;
	}
 
 	tc_desc.rx_tc_num = priv->num_rx_tc;
 	tc_desc.tx_tc_num = priv->num_tx_tc;
 		/*todo -= add more types */
 		RTE_PTYPE_L2_ETHER,
 		RTE_PTYPE_L3_IPV4,
 		RTE_PTYPE_L3_IPV4_EXT,
 		RTE_PTYPE_L3_IPV6,
 		RTE_PTYPE_L3_IPV6_EXT,
 		goto init_err;
 	}
 
 	ret = dpaa2_dev_ep_init(dpaa2_dev, priv);
 	if (ret) {
 		DPAA2_PMD_ERR("Failure in get dpni@%d's endpoint, err code %d",
 	DPAA2_PMD_INFO("%s: netdev created, connected to %s",
 		eth_dev->data->name, priv->ep_name);
 
 	return 0;
 init_err:
 	dpaa2_dev_close(eth_dev);