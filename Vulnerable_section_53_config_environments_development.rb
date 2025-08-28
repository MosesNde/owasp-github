   config.action_mailer.default_url_options = { :host => "localhost:3000" }
 
   # Authorization
   config.default_permissions = ["#{Backoffice::AdminsController.controller_path}:write",
                                 "#{Backoffice::AdminsController.controller_path}:read",
                                 "#{Backoffice::CategoriesController.controller_path}:read",
                                 "#{Backoffice::DashboardController.controller_path}:read",
                                 "#{Backoffice::MessageController.controller_path}:write",
                                 "#{Devise::SessionsController.controller_path}:write",
                                "#{Site::HomeController.controller_path}:read"]
   config.default_roles = [
     { name: "Administrator",
       is_admin: true,
       is_admin: false,
       is_opt: false,
       is_member: true,
      permissions: ["#{Site::HomeController.controller_path}:read"],
       except_permissions: ["*"] },
   ]
 