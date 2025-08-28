# typed: true
 class BackofficeController < ApplicationController
  before_action :authenticate_user!
   before_action :user_can_read, only: [:index]
   before_action :user_can_write, only: [:new, :create, :edit, :update, :destroy]
   before_action :get_instance, only: [:edit, :update, :destroy]
   layout "backoffice"
 
   def policy(user)
    UserPolicy.new(user, get_controller_name)
   end
 
  def policy_class
    UserPolicy
   end
 
   protected
                                 object_name: default_class.model_name.human,
                                 :gender => :n)
         }
        format.json { render :index, status: :created }
       else
         format.html { render :new, status: :unprocessable_entity }
        format.json { render json: @object.errors, status: :unprocessable_entity }
       end
     end
   end
           redirect_to get_default_path,
                       notice: t("layout.action_text.updated", object_name: default_class.model_name.human, :gender => :n)
         }
        format.json { render :index, status: :ok }
       else
         format.html { render :edit, status: :unprocessable_entity }
        format.json { render json: @object.errors, status: :unprocessable_entity }
       end
     end
   end
                                 name: default_name,
                                 :gender => :n)
         }
        format.json { head :no_content }
       else
         format.html { render :index, status: :unprocessable_entity }
        format.json { render json: @object.errors, status: :unprocessable_entity }
       end
     end
   end
 
  def get_controller_name
    "backoffice"
  end

   def user_can_read
     authorize get_controller_name, :has_read_permission?, policy_class: UserPolicy
   end
     authorize get_controller_name, :has_read_and_write_permission?, policy_class: UserPolicy
   end
 
   def get_instance
     @object = default_class.find(params[:id])
   end
 
   def get_default_service
     class_name = default_class_name
    constant_class = "Backoffice::#{class_name.pluralize}Controller::#{class_name}Service".constantize
    constant_class
  end

  def get_default_path
   end
 
   def permitted_params
     "#{default_class_name}Policy".constantize
   end
 
  private

   def default_class_name
     controller_name.classify
   end