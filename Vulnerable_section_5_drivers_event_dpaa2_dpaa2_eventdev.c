 /* SPDX-License-Identifier: BSD-3-Clause
 * Copyright 2017,2019-2024 NXP
  */
 
 #include <assert.h>
 	rx_queue_cfg.dest_cfg.dest_type = DPCI_DEST_DPCON;
 	rx_queue_cfg.dest_cfg.dest_id = dpcon_dev->dpcon_id;
 	rx_queue_cfg.dest_cfg.priority = DPAA2_EVENT_DEFAULT_DPCI_PRIO;
 
 	dpci_dev->rx_queue[DPAA2_EVENT_DPCI_PARALLEL_QUEUE].cb =
 		dpaa2_eventdev_process_parallel;