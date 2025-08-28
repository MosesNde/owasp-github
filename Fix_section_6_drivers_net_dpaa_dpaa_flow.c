 /* SPDX-License-Identifier: BSD-3-Clause
 * Copyright 2017-2019,2021-2025 NXP
  */
 
 /* System headers */
 	/* FM PCD Enable */
 	ret = fm_pcd_enable(pcd_handle);
 	if (ret) {
 		DPAA_PMD_ERR("fm_pcd_enable: Failed");
		fm_pcd_close(pcd_handle);
		fm_close(fman_handle);
 		return -1;
 	}
 