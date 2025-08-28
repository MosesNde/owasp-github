 #
 # It's strongly recommended that you check this file into your version control system.
 
ActiveRecord::Schema.define(version: 2024_03_28_171633) do
 
   # These are extensions that must be enabled in order to support this database
   enable_extension "plpgsql"
     t.integer "advertisements_count", default: 0
   end
 
   create_table "permissions", force: :cascade do |t|
     t.string "name", limit: 255, null: false
     t.datetime "created_at", precision: 6, null: false
     t.index ["role_id", "permission_id"], name: "index_permissions_roles_on_role_id_and_permission_id"
   end
 
   create_table "roles", force: :cascade do |t|
     t.string "name", limit: 255, null: false
     t.datetime "created_at", precision: 6, null: false
   add_foreign_key "active_storage_attachments", "active_storage_blobs", column: "blob_id"
   add_foreign_key "advertisements", "categories"
   add_foreign_key "advertisements", "users"
 end