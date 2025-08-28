   if (NamespaceData != NULL) {
     FreeZero (NamespaceData);
   }
  if (EFI_ERROR(Status) && Device != NULL) {
    FreeZero (Device);
  }
   return Status;
 }
 
 
 Exit:
   if (EFI_ERROR (Status)) {
      if (Private != NULL) {
        if (Private->ControllerData != NULL) {
          FreeZero (Private->ControllerData);
        }
        if (Private->Buffer != NULL) {
          nvme_free_pages(Private->Buffer);
        }
        FreeZero (Private);
       }
   }
 