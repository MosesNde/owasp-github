# typed: false
 class BackofficeController < ApplicationController
  before_action :authenticate_admin!
   before_action :user_can_read, only: [:index]
   before_action :user_can_write, only: [:new, :create, :edit, :update, :destroy]
   before_action :get_instance, only: [:edit, :update, :destroy]
   layout "backoffice"
 
   def policy(user)
    UserPolicy.new(user, controller_name)
   end
 
  def pundit_user
    current_admin
   end
 
   protected
                                 object_name: default_class.model_name.human,
                                 :gender => :n)
         }
       else
         format.html { render :new, status: :unprocessable_entity }
       end
     end
   end
           redirect_to get_default_path,
                       notice: t("layout.action_text.updated", object_name: default_class.model_name.human, :gender => :n)
         }
       else
         format.html { render :edit, status: :unprocessable_entity }
       end
     end
   end
                                 name: default_name,
                                 :gender => :n)
         }
       else
         format.html { render :index, status: :unprocessable_entity }
       end
     end
   end
 
   def user_can_read
     authorize get_controller_name, :has_read_permission?, policy_class: UserPolicy
   end
     authorize get_controller_name, :has_read_and_write_permission?, policy_class: UserPolicy
   end
 
  def get_default_path
  end

  private

  def get_controller_name
    controller_path
  end

   def get_instance
     @object = default_class.find(params[:id])
   end
 
   def get_default_service
     class_name = default_class_name
    "Backoffice::#{class_name.pluralize}Controller::#{class_name}Service".constantize
   end
 
   def permitted_params
     "#{default_class_name}Policy".constantize
   end
 
   def default_class_name
     controller_name.classify
   end