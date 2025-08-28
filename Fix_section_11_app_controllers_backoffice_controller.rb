 # typed: false
# string_frozen_literal: true

 class BackofficeController < ApplicationController
   before_action :authenticate_admin!
   before_action :user_can_read, only: [:index]
   layout "backoffice"
 
   def policy(user)
    UserPolicy.new(user, controller_path)
   end
 
   def pundit_user