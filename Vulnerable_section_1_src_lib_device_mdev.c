 int mdev_create(unsigned pcnt, const char** names, const char** values, lldev_t* odev,
                 unsigned idx, char** bus_names, unsigned bus_cnt)
 {
    dev_multi_t* obj = (dev_multi_t*)malloc(sizeof(dev_multi_t));
     int res;
     unsigned i;
     const uint8_t* uuid_master;
 
     memset(obj, 0, sizeof(*obj));
 
     // Creating sub-device
 
         res = lowlevel_create(pcnt, names, values, &obj->real[i], 0, NULL, 0);
         if (res)
            return res;
 
         if (i == 0) {
             uuid_master = lowlevel_get_uuid(obj->real[i]);
     obj->lldev.ops = &s_mdev_ops;
 
     // Create virtual device
    res = usdr_device_base_create(&obj->virt_dev, &obj->lldev);
    if (res)
         goto error_init;
 
     obj->lldev.pdev = &obj->virt_dev;

     obj->virt_dev.destroy = &_mdev_destroy;
     obj->virt_dev.create_stream = &_mdev_create_stream;
     obj->virt_dev.unregister_stream = &_mdev_unregister_stream;
     obj->virt_dev.timer_op = &_mdev_stream_sync;
     obj->virt_dev.vfs_get_single_object = &_mdev_get_obj;
 
     // Set multi dev for master node
    res = usdr_device_vfs_obj_val_set_by_path(obj->real[0]->pdev, "/ll/mdev", (uintptr_t)&obj->lldev);
 
     USDR_LOG("DSTR", USDR_LOG_WARNING, "Creating multi device with %d nodes, each %d/%d RX/TX chans, MDEV captured: %d\n",
              obj->cnt, obj->rx_chans, obj->tx_chans, res == 0 ? 1 : 0);

     *odev = &obj->lldev;
     return 0;
 

 error_init:
    return -ENOTSUP;
 }