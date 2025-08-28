# typed: false
 class Backoffice::RolesController < BackofficeController
   def index
     super
   def get_default_path
     backoffice_roles_path
   end
 end