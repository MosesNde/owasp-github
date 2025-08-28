   config.action_mailer.default_url_options = { :host => "localhost:3000" }
 
   # Authorization
  config.default_password = "123456"

   config.default_permissions = ["#{Backoffice::AdminsController.controller_path}:write",
                                 "#{Backoffice::AdminsController.controller_path}:read",
                                 "#{Backoffice::CategoriesController.controller_path}:read",
                                 "#{Backoffice::DashboardController.controller_path}:read",
                                 "#{Backoffice::MessageController.controller_path}:write",
                                 "#{Devise::SessionsController.controller_path}:write",
                                "#{Site::HomeController.controller_path}:read",
                                "#{Site::Profile::DashboardController.controller_path}:read",
                                "#{Site::Profile::DashboardController.controller_path}:write",
                                "#{Site::Profile::AdvertisementsController.controller_path}:read",
                                "#{Site::Profile::AdvertisementsController.controller_path}:write"]
   config.default_roles = [
     { name: "Administrator",
       is_admin: true,
       is_admin: false,
       is_opt: false,
       is_member: true,
      permissions: ["#{Site::HomeController.controller_path}:read",
                    "#{Site::Profile::DashboardController.controller_path}:read",
                    "#{Site::Profile::DashboardController.controller_path}:write",
                    "#{Site::Profile::AdvertisementsController.controller_path}:read",
                    "#{Site::Profile::AdvertisementsController.controller_path}:write"],
       except_permissions: ["*"] },
   ]
 