 # typed: true
 class Member < User
   has_many :advertisements, class_name: "Advertisements"
 
   validate :can_change_role?, on: :update
 
   define_attribute_methods
 
   def role_ids=(new_role_ids)
     @can_change_roles = true
 
     member_role = Role.find_by name: Rails.configuration.default_roles.find { |r| r[:is_member] }[:name]
 
    unless new_role_ids.empty?
       super [member_role.id]
       return
     end