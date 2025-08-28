 class Backoffice::RolesController::RoleService
   def self.create(params)
     role = Role.new(params)
   end
 
   def self.update(params, role)
    role.update(params)
   end
 
   def self.destroy(role)