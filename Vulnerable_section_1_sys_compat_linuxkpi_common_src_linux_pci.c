 linuxkpi_pci_iounmap(struct pci_dev *pdev, void *res)
 {
 	struct pci_mmio_region *mmio, *p;
 
 	TAILQ_FOREACH_SAFE(mmio, &pdev->mmio, next, p) {
		if ((bus_space_handle_t)res < rman_get_bushandle(mmio->res) ||
		    (bus_space_handle_t)res >= rman_get_bushandle(mmio->res) +
					       rman_get_size(mmio->res))
			continue;
 		bus_release_resource(pdev->dev.bsddev,
 		    mmio->type, mmio->rid, mmio->res);
 		TAILQ_REMOVE(&pdev->mmio, mmio, next);