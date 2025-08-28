 # application.js, application.css, and all non-JS/CSS in the app/assets
 # folder are already added.
 # Rails.application.config.assets.precompile += %w( admin.js admin.css )
Rails.application.config.assets.precompile += %w(bootstrap.min.js @popperjs/core popper.js)
Rails.application.config.assets.precompile += %w(backoffice.js site.js)
 # config/initializers/assets.rb