 /* SPDX-License-Identifier: BSD-3-Clause
 * Copyright 2021,2024-2025 NXP
  */
 
 #include <stdbool.h>
 	}
 	/* Read mapping size and physical address expressed in hexa(base 16) */
 	uio_map_size = strtol(uio_map_size_str, NULL, 16);
	if (uio_map_size <= 0 || uio_map_size > INT_MAX){
		ENETFEC_PMD_ERR("Invalid mapping size: %u.",uio_map_size);
		return NULL;
	}
 	uio_map_p_addr = strtol(uio_map_p_addr_str, NULL, 16);
 
 	if (uio_map_id == 0) {