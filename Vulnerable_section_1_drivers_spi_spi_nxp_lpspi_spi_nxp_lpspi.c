 	LPSPI_Type *base = (LPSPI_Type *)DEVICE_MMIO_NAMED_GET(dev, reg_base);
 	struct spi_mcux_data *data = dev->data;
 	struct lpspi_driver_data *lpspi_data = (struct lpspi_driver_data *)data->driver_data;
	int ret;
 
 	spi_context_lock(&data->ctx, asynchronous, cb, userdata, spi_cfg);
 
 	lpspi_data->word_size_bytes = SPI_WORD_SIZE_GET(spi_cfg->operation) / BITS_PER_BYTE;
 	if (lpspi_data->word_size_bytes > 4) {
 		LOG_ERR("Maximum 4 byte word size");
 		ret = -EINVAL;
		return ret;
 	}
 
	spi_context_buffers_setup(&data->ctx, tx_bufs, rx_bufs, lpspi_data->word_size_bytes);
 
 	ret = spi_mcux_configure(dev, spi_cfg);
 	if (ret) {
		return ret;
 	}
 
 	LPSPI_FlushFifo(base, true, true);
 	LPSPI_ClearStatusFlags(base, (uint32_t)kLPSPI_AllStatusFlag);
 	LPSPI_DisableInterrupts(base, (uint32_t)kLPSPI_AllInterruptEnable);
 
 	LOG_DBG("Starting LPSPI transfer");
	spi_context_cs_control(&data->ctx, true);
 
 	LPSPI_SetFifoWatermarks(base, 0, 0);
 	LPSPI_Enable(base, true);
 	LPSPI_EnableInterrupts(base, (uint32_t)kLPSPI_TxInterruptEnable |
 				     (uint32_t)kLPSPI_RxInterruptEnable);
 
	return spi_context_wait_for_completion(&data->ctx);
 }
 
 static int spi_mcux_transceive_sync(const struct device *dev, const struct spi_config *spi_cfg,