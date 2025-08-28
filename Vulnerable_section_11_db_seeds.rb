 
 if Role.all.empty?
   puts "Adding default roles"
  Role.upsert_all([
    { name: "administrator", created_at: current_datetime, updated_at: current_datetime },
    { name: "operator", created_at: current_datetime, updated_at: current_datetime },
    { name: "member", created_at: current_datetime, updated_at: current_datetime },
  ])
   puts "All roles were added!"
 end