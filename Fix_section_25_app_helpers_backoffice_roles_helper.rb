# typed: true
 module Backoffice::RolesHelper
   def permission_options
     Permission.all