 #
 # It's strongly recommended that you check this file into your version control system.
 
ActiveRecord::Schema.define(version: 2024_05_13_160045) do
 
   # These are extensions that must be enabled in order to support this database
   enable_extension "plpgsql"
     t.integer "advertisements_count", default: 0
   end
 
  create_table "comments", force: :cascade do |t|
    t.string "title", limit: 100
    t.text "body"
    t.bigint "user_id", null: false
    t.bigint "advertisement_id", null: false
    t.datetime "created_at", precision: 6, null: false
    t.datetime "updated_at", precision: 6, null: false
    t.index ["advertisement_id"], name: "index_comments_on_advertisement_id"
    t.index ["user_id"], name: "index_comments_on_user_id"
  end

   create_table "permissions", force: :cascade do |t|
     t.string "name", limit: 255, null: false
     t.datetime "created_at", precision: 6, null: false
     t.index ["role_id", "permission_id"], name: "index_permissions_roles_on_role_id_and_permission_id"
   end
 
  create_table "rating_rates", id: :serial, force: :cascade do |t|
    t.decimal "value", precision: 11, scale: 2, default: "0.0"
    t.string "author_type", limit: 50, null: false
    t.integer "author_id", null: false
    t.string "resource_type", limit: 50, null: false
    t.integer "resource_id", null: false
    t.string "scopeable_type", limit: 50
    t.integer "scopeable_id"
    t.datetime "created_at", null: false
    t.datetime "updated_at", null: false
    t.index ["author_type", "author_id", "resource_type", "resource_id", "scopeable_type", "scopeable_id"], name: "index_rating_rates_on_author_and_resource_and_scopeable", unique: true
    t.index ["author_type", "author_id"], name: "index_rating_rates_on_author_type_and_author_id"
    t.index ["resource_type", "resource_id"], name: "index_rating_rates_on_resource_type_and_resource_id"
    t.index ["scopeable_type", "scopeable_id"], name: "index_rating_rates_on_scopeable_type_and_scopeable_id"
  end

  create_table "rating_ratings", id: :serial, force: :cascade do |t|
    t.decimal "average", precision: 11, scale: 2, default: "0.0"
    t.decimal "estimate", precision: 11, scale: 2, default: "0.0"
    t.integer "sum", default: 0
    t.integer "total", default: 0
    t.string "resource_type", limit: 50, null: false
    t.integer "resource_id", null: false
    t.string "scopeable_type", limit: 50
    t.integer "scopeable_id"
    t.datetime "created_at", null: false
    t.datetime "updated_at", null: false
    t.index ["resource_type", "resource_id", "scopeable_type", "scopeable_id"], name: "index_rating_rating_on_resource_and_scopeable", unique: true
    t.index ["resource_type", "resource_id"], name: "index_rating_ratings_on_resource_type_and_resource_id"
    t.index ["scopeable_type", "scopeable_id"], name: "index_rating_ratings_on_scopeable_type_and_scopeable_id"
  end

   create_table "roles", force: :cascade do |t|
     t.string "name", limit: 255, null: false
     t.datetime "created_at", precision: 6, null: false
   add_foreign_key "active_storage_attachments", "active_storage_blobs", column: "blob_id"
   add_foreign_key "advertisements", "categories"
   add_foreign_key "advertisements", "users"
  add_foreign_key "comments", "advertisements"
  add_foreign_key "comments", "users"
 end