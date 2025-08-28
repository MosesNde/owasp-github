# typed: false
 # This file is auto-generated from the current state of the database. Instead
 # of editing this file, please use the migrations feature of Active Record to
 # incrementally modify your database, and then regenerate this schema definition.
 #
 # It's strongly recommended that you check this file into your version control system.
 
ActiveRecord::Schema.define(version: 2024_03_12_145631) do
 
   # These are extensions that must be enabled in order to support this database
   enable_extension "plpgsql"
     t.datetime "updated_at", precision: 6, null: false
     t.integer "price_cents"
     t.date "finish_date"
     t.index ["category_id"], name: "index_advertisements_on_category_id"
     t.index ["user_id"], name: "index_advertisements_on_user_id"
   end
 
   create_table "categories", force: :cascade do |t|
     t.string "description", limit: 60
     t.datetime "created_at", precision: 6, null: false
     t.datetime "updated_at", precision: 6, null: false
   end
 
   create_table "permissions", force: :cascade do |t|