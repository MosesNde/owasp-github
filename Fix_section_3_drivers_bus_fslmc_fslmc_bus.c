 /* SPDX-License-Identifier: BSD-3-Clause
  *
 *   Copyright 2016,2018-2025 NXP
  *
  */
 
 		goto scan_fail;
 
 	/* Scan devices on the group */
	snprintf(fslmc_dirpath, sizeof(fslmc_dirpath), "%s/%s",
			SYSFS_FSL_MC_DEVICES, group_name);
 	dir = opendir(fslmc_dirpath);
 	if (!dir) {
 		DPAA2_BUS_ERR("Unable to open VFIO group directory");