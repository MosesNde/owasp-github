# typed: strict
 Rails.application.configure do
   # Settings specified here will take precedence over those in config/application.rb.
 
   config.action_mailer.default_url_options = { :host => "localhost:3000" }
 
   # Authorization
  config.default_permissions = ["#{Backoffice::AdminsController.controller_path}:write",
                                "#{Backoffice::AdminsController.controller_path}:read",
                                "#{Backoffice::CategoriesController.controller_path}:read",
                                "#{Backoffice::CategoriesController.controller_path}:write",
                                "#{Backoffice::MembersController.controller_path}:write",
                                "#{Backoffice::MembersController.controller_path}:read",
                                "#{Backoffice::RolesController.controller_path}:write",
                                "#{Backoffice::RolesController.controller_path}:read",
                                "#{Backoffice::PermissionsController.controller_path}:read",
                                "#{Backoffice::DashboardController.controller_path}:read",
                                "#{Backoffice::MessageController.controller_path}:write",
                                "#{Devise::SessionsController.controller_path}:write",
                                "#{Site::HomeController.controller_path}:read"]
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
     is_member: false,
     permissions: ["*"],
     except_permissions: ["#{Backoffice::AdminsController.controller_path}:write",
                          "#{Backoffice::MembersController.controller_path}:write",
                          "#{Backoffice::RolesController.controller_path}:write",
                          "#{Backoffice::PermissionsController.controller_path}:write",
                          "#{Backoffice::PermissionsController.controller_path}:write"] },
    { name: "Member",
      is_admin: false,
      is_opt: false,
      is_member: true,
      permissions: ["#{Site::HomeController.controller_path}:read"],
      except_permissions: ["*"] },
   ]
 
   # Print deprecation notices to the Rails logger.