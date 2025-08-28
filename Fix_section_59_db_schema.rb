 # This file is auto-generated from the current state of the database. Instead
 # of editing this file, please use the migrations feature of Active Record to
 # incrementally modify your database, and then regenerate this schema definition.
 #
 # It's strongly recommended that you check this file into your version control system.
 
ActiveRecord::Schema.define(version: 2024_03_28_171633) do
 
   # These are extensions that must be enabled in order to support this database
   enable_extension "plpgsql"
     t.datetime "updated_at", precision: 6, null: false
     t.integer "price_cents"
     t.date "finish_date"
    t.bigint "ahoy_visit_id"
    t.index ["ahoy_visit_id"], name: "index_advertisements_on_ahoy_visit_id"
     t.index ["category_id"], name: "index_advertisements_on_category_id"
     t.index ["user_id"], name: "index_advertisements_on_user_id"
   end
 
  create_table "ahoy_events", force: :cascade do |t|
    t.bigint "visit_id"
    t.bigint "user_id"
    t.string "name"
    t.jsonb "properties"
    t.datetime "time"
    t.index ["name", "time"], name: "index_ahoy_events_on_name_and_time"
    t.index ["properties"], name: "index_ahoy_events_on_properties", opclass: :jsonb_path_ops, using: :gin
    t.index ["user_id"], name: "index_ahoy_events_on_user_id"
    t.index ["visit_id"], name: "index_ahoy_events_on_visit_id"
  end

  create_table "ahoy_visits", force: :cascade do |t|
    t.string "visit_token"
    t.string "visitor_token"
    t.bigint "user_id"
    t.string "ip"
    t.text "user_agent"
    t.text "referrer"
    t.string "referring_domain"
    t.text "landing_page"
    t.string "browser"
    t.string "os"
    t.string "device_type"
    t.string "country"
    t.string "region"
    t.string "city"
    t.float "latitude"
    t.float "longitude"
    t.string "utm_source"
    t.string "utm_medium"
    t.string "utm_term"
    t.string "utm_content"
    t.string "utm_campaign"
    t.string "app_version"
    t.string "os_version"
    t.string "platform"
    t.datetime "started_at"
    t.index ["user_id"], name: "index_ahoy_visits_on_user_id"
    t.index ["visit_token"], name: "index_ahoy_visits_on_visit_token", unique: true
  end

   create_table "categories", force: :cascade do |t|
     t.string "description", limit: 60
     t.datetime "created_at", precision: 6, null: false
     t.datetime "updated_at", precision: 6, null: false
    t.integer "advertisements_count", default: 0
   end
 
   create_table "permissions", force: :cascade do |t|