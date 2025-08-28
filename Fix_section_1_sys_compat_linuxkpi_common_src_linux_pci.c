 linuxkpi_pci_iounmap(struct pci_dev *pdev, void *res)
 {
 	struct pci_mmio_region *mmio, *p;
	bus_space_handle_t bh = (bus_space_handle_t)res;
 
 	TAILQ_FOREACH_SAFE(mmio, &pdev->mmio, next, p) {
		if (pdev->want_iomap_res) {
			if (res != mmio->res)
				continue;
		} else {
			if (bh <  rman_get_bushandle(mmio->res) ||
			    bh >= rman_get_bushandle(mmio->res) +
				  rman_get_size(mmio->res))
				continue;
		}
 		bus_release_resource(pdev->dev.bsddev,
 		    mmio->type, mmio->rid, mmio->res);
 		TAILQ_REMOVE(&pdev->mmio, mmio, next);