 class Backoffice::MembersController < BackofficeController
   def index
     super
 
   protected
 
  def get_controller_name
    "#{super}/#{controller_name}"
  end

   def get_default_path
     backoffice_members_path
   end