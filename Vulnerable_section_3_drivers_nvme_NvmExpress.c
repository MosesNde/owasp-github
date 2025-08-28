   if (NamespaceData != NULL) {
     FreeZero (NamespaceData);
   }
   return Status;
 }
 
 
 Exit:
   if (EFI_ERROR (Status)) {
      if ((Private != NULL) && (Private->ControllerData != NULL)) {
         FreeZero (Private->ControllerData);
       }
   }
 