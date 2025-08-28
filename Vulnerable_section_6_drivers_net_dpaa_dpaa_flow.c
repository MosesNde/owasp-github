 /* SPDX-License-Identifier: BSD-3-Clause
 * Copyright 2017-2019,2021-2024 NXP
  */
 
 /* System headers */
 	/* FM PCD Enable */
 	ret = fm_pcd_enable(pcd_handle);
 	if (ret) {
		fm_close(fman_handle);
		fm_pcd_close(pcd_handle);
 		DPAA_PMD_ERR("fm_pcd_enable: Failed");
 		return -1;
 	}
 