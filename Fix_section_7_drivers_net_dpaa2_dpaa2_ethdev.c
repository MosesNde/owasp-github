 		return 0;
 }
 
static uint32_t dpaa2_speed_to_rte_link_speed(enum dpmac_link_speed dpmac_speed)
{
	switch (dpmac_speed) {
	case DPMAC_LINK_SPEED_10M:
		return RTE_ETH_LINK_SPEED_10M;
	case DPMAC_LINK_SPEED_100M:
		return RTE_ETH_LINK_SPEED_100M;
	case DPMAC_LINK_SPEED_1G:
		return RTE_ETH_LINK_SPEED_1G;
	case DPMAC_LINK_SPEED_2_5G:
		return RTE_ETH_LINK_SPEED_2_5G;
	case DPMAC_LINK_SPEED_5G:
		return RTE_ETH_LINK_SPEED_5G;
	case DPMAC_LINK_SPEED_10G:
		return RTE_ETH_LINK_SPEED_10G;
	case DPMAC_LINK_SPEED_25G:
		return RTE_ETH_LINK_SPEED_25G;
	case DPMAC_LINK_SPEED_40G:
		return RTE_ETH_LINK_SPEED_40G;
	case DPMAC_LINK_SPEED_50G:
		return RTE_ETH_LINK_SPEED_50G;
	case DPMAC_LINK_SPEED_100G:
		return RTE_ETH_LINK_SPEED_100G;
	default:
		return 0;
	}
}

static uint32_t dpaa2_dev_get_speed_capability(struct rte_eth_dev *dev)
{
	struct fsl_mc_io *dpni = (struct fsl_mc_io *)dev->process_private;
	struct dpaa2_dev_priv *priv = dev->data->dev_private;
	enum dpmac_link_speed speed;
	uint32_t dpmac_speed_cap;
	uint32_t speed_capa = 0;
	int ret;

	/* The dpni_get_mac_supported_eth_if() API is only available starting
	 * with DPNI ver 8.6.
	 */
	if (dpaa2_dev_cmp_dpni_ver(priv, DPNI_GET_MAC_SUPPORTED_IFS_VER_MAJOR,
				   DPNI_GET_MAC_SUPPORTED_IFS_VER_MINOR) < 0)
		goto fallback;

	if (priv->ep_dev_type != DPAA2_MAC)
		goto fallback;

	ret = dpni_get_mac_speed_capability(dpni, CMD_PRI_LOW, priv->token,
					    &dpmac_speed_cap);
	if (ret < 0) {
		DPAA2_PMD_WARN("dpni_get_mac_speed_capability() failed with %d", ret);
		goto fallback;
	}
	for (speed = DPMAC_LINK_SPEED_10M; speed < DPMAC_LINK_SPEED_MAX; speed++) {
		if ((dpmac_speed_cap & (1 << speed)) == 0)
			continue;

		speed_capa |= dpaa2_speed_to_rte_link_speed(speed);
	}

	return speed_capa;

fallback:
	speed_capa = RTE_ETH_LINK_SPEED_1G | RTE_ETH_LINK_SPEED_2_5G |
		RTE_ETH_LINK_SPEED_10G;

	if (dpaa2_svr_family == SVR_LX2160A)
		speed_capa |= RTE_ETH_LINK_SPEED_25G | RTE_ETH_LINK_SPEED_40G |
			RTE_ETH_LINK_SPEED_50G | RTE_ETH_LINK_SPEED_100G;

	return speed_capa;
}

 static int
 dpaa2_dev_info_get(struct rte_eth_dev *dev,
 	struct rte_eth_dev_info *dev_info)
 					dev_rx_offloads_nodis;
 	dev_info->tx_offload_capa = dev_tx_offloads_sup |
 					dev_tx_offloads_nodis;
 	dev_info->dev_capa &= ~RTE_ETH_DEV_CAPA_FLOW_RULE_KEEP;
 
 	dev_info->max_hash_mac_addrs = 0;
 	dev_info->default_txportconf.ring_size = CONG_ENTER_TX_THRESHOLD;
 	dev_info->default_rxportconf.ring_size = DPAA2_RX_DEFAULT_NBDESC;
 
	dev_info->speed_capa = priv->speed_capa;
 
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
 
	ret = dpni_get_api_version(dpni_dev, CMD_PRI_LOW, &priv->dpni_ver_major,
				   &priv->dpni_ver_minor);
	if (ret) {
		DPAA2_PMD_ERR("Failure in get dpni@%d API version, err code %d",
			hw_id, ret);
		goto init_err;
	}

 	ret = dpaa2_dev_ep_init(dpaa2_dev, priv);
 	if (ret) {
 		DPAA2_PMD_ERR("Failure in get dpni@%d's endpoint, err code %d",
 	DPAA2_PMD_INFO("%s: netdev created, connected to %s",
 		eth_dev->data->name, priv->ep_name);
 

	priv->speed_capa = dpaa2_dev_get_speed_capability(eth_dev);

 	return 0;
 init_err:
 	dpaa2_dev_close(eth_dev);