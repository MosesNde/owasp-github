# typed: false
 class Backoffice::MembersController < BackofficeController
   def index
     super
 
   protected
 
   def get_default_path
     backoffice_members_path
   end