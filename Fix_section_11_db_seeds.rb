 
 if Role.all.empty?
   puts "Adding default roles"
  roles = Rails.configuration.default_roles.map do |role|
    { name: role[:name], created_at: current_datetime, updated_at: current_datetime }
  end
  Role.upsert_all(roles)
   puts "All roles were added!"
 end