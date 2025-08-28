 class ApplicationController < ActionController::Base
   include Pundit::Authorization
 
  rescue_from Pundit::NotAuthorizedError, with: :user_not_authorized

   layout :layout_by_resource
 
   protected
       "application"
     end
   end

  def user_not_authorized
    flash[:alert] = t "layout.action_text.not_authorized"
    redirect_back(fallback_location: root_path)
  end
 end