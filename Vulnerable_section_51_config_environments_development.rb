                                 "#{Site::Profile::DashboardController.controller_path}:read",
                                 "#{Site::Profile::DashboardController.controller_path}:write",
                                 "#{Site::Profile::AdvertisementsController.controller_path}:read",
                                "#{Site::Profile::AdvertisementsController.controller_path}:write"]
   config.default_roles = [
     { name: "Administrator",
      is_admin: true,
      is_opt: false,
      is_member: false,
      permissions: ["*"],
      except_permissions: ["#{Backoffice::MembersController.controller_path}:write"] },
     { name: "Operator",
      is_admin: false,
      is_opt: true,
                           "#{Backoffice::MembersController.controller_path}:write",
                           "#{Backoffice::RolesController.controller_path}:write",
                           "#{Backoffice::PermissionsController.controller_path}:write",
                          "#{Backoffice::PermissionsController.controller_path}:write"] },
     { name: "Member",
       is_admin: false,
       is_opt: false,
                     "#{Site::Profile::DashboardController.controller_path}:write",
                     "#{Site::Profile::AdvertisementsController.controller_path}:read",
                     "#{Site::Profile::AdvertisementsController.controller_path}:write"],
      except_permissions: ["*"] },
   ]
 
   # Print deprecation notices to the Rails logger.