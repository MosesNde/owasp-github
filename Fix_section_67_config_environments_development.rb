# typed: false
 Rails.application.configure do
   # Settings specified here will take precedence over those in config/application.rb.
 
                                 "#{Backoffice::MessageController.controller_path}:write",
                                 "#{Devise::SessionsController.controller_path}:write",
                                 "#{Site::HomeController.controller_path}:read",
                                "#{Site::CommentsController.controller_path}:read",
                                "#{Site::CommentsController.controller_path}:write",
                                 "#{Site::Profile::DashboardController.controller_path}:read",
                                 "#{Site::Profile::DashboardController.controller_path}:write",
                                 "#{Site::Profile::AdvertisementsController.controller_path}:read",
       permissions: ["#{Site::HomeController.controller_path}:read",
                     "#{Site::Profile::DashboardController.controller_path}:read",
                     "#{Site::Profile::DashboardController.controller_path}:write",
                    "#{Site::CommentsController.controller_path}:read",
                    "#{Site::CommentsController.controller_path}:write",
                    "#{Site::Profile::MemberProfileController.controller_path}:read",
                     "#{Site::Profile::AdvertisementsController.controller_path}:read",
                     "#{Site::Profile::AdvertisementsController.controller_path}:write"],
       except_permissions: ["#{BackofficeController.controller_path}"] },
   # Use an evented file watcher to asynchronously detect changes in source code,
   # routes, locales, etc. This feature depends on the listen gem.
   config.file_watcher = ActiveSupport::EventedFileUpdateChecker

  config.action_controller.asset_host = "localhost:3000"
 end