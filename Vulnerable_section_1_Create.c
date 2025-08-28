 			       dv->devname);
 			return 1;
 		}
		if (!fstat_is_blkdev(fd, dv->devname, &rdev))
 			return 1;
 		info->disk.major = major(rdev);
 		info->disk.minor = minor(rdev);
 	}
 	if (st->ss->add_to_super(st, &info->disk, fd, dv->devname,
 				 dv->data_offset)) {
 		ioctl(mdfd, STOP_ARRAY, NULL);
 		return 1;
 	}
 	st->ss->getinfo_super(st, info, NULL);
 		*zero_pid = write_zeroes_fork(fd, s, st, dv);
 		if (*zero_pid <= 0) {
 			ioctl(mdfd, STOP_ARRAY, NULL);
 			return 1;
 		}
 	}