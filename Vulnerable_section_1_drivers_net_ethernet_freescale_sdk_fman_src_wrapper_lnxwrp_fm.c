 
     if ((p_LnxWrpFmDev = ReadFmDevTreeNode(of_dev)) == NULL)
         return -EIO;
    if (ConfigureFmDev(p_LnxWrpFmDev) != E_OK)
         return -EIO;
    if (InitFmDev(p_LnxWrpFmDev) != E_OK)
         return -EIO;
 
     /* IOCTL ABI checking */
     LnxWrpPCDIOCTLEnumChecking();
     /* Register to the /dev for IOCTL API */
     /* Register dynamically a new major number for the character device: */
     if ((p_LnxWrpFmDev->major = register_chrdev(0, p_LnxWrpFmDev->name, &fm_fops)) <= 0) {
         REPORT_ERROR(MAJOR, E_INVALID_STATE, ("Failed to allocate a major number for device \"%s\"", p_LnxWrpFmDev->name));
         return -EIO;
     }
     p_LnxWrpFmDev->fm_class = class_create(p_LnxWrpFmDev->name);
     if (IS_ERR(p_LnxWrpFmDev->fm_class)) {
         unregister_chrdev(p_LnxWrpFmDev->major, p_LnxWrpFmDev->name);
         REPORT_ERROR(MAJOR, E_INVALID_STATE, ("class_create error fm_class"));
         return -EIO;
     }