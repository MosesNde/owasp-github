 # typed: false
 class Advertisement < ApplicationRecord
   extend T::Sig
  belongs_to :category, counter_cache: :advertisements_count
   belongs_to :user
  visitable :ahoy_visit
 
   validates :title, :description, :category, :picture, :price, presence: true
 
   has_one_attached :picture
 
   scope :new_arrivals, ->(size = 10) { before_finish_date.limit(size).order(created_at: :desc) }
  scope :by_category_description, ->(category_description, size = 10) {
          before_finish_date
            .joins("JOIN categories on categories.id = category_id")
            .where("categories.description = :category_description", { category_description: category_description })
            .limit(size)
            .order(created_at: :desc)
        }
   scope :related_items, ->(id, category_id, size = 10) {
           before_finish_date
             .where("id != :id AND category_id = :category_id", { id: id, category_id: category_id })
         }
   scope :for_member, ->(member) { where(user_id: member.id) }
   scope :before_finish_date, -> { where("finish_date >= CURRENT_DATE") }
  scope :most_seem_advertisements, -> {
          query = <<~EOL
            \"ahoy_events\".properties @> '{\"action\": \"show\", \"controller\": \"site/advertisements\"}'
            AND advertisements.finish_date >= CURRENT_DATE
          EOL
          where(query)
            .joins("JOIN \"ahoy_events\" ON (\"ahoy_events\".properties->>'id')::INT = advertisements.id")
            .joins("JOIN \"ahoy_visits\" ON \"ahoy_visits\".id = \"ahoy_events\".visit_id")
            .select("advertisements.title as advertisement_title", "COUNT(advertisements.id) as total_accesses")
            .group("advertisements.title")
        }
  scope :most_seem_advertisements_for_user, ->(user_id) {
          query = <<~EOL
            \"ahoy_events\".properties @> '{\"action\": \"show\", \"controller\": \"site/advertisements\"}'
            AND advertisements.finish_date >= CURRENT_DATE
            AND advertisements.user_id = :user_id
          EOL
          where(query, { user_id: user_id })
            .joins("JOIN \"ahoy_events\" ON (\"ahoy_events\".properties->>'id')::INT = advertisements.id")
            .joins("JOIN \"ahoy_visits\" ON \"ahoy_visits\".id = \"ahoy_events\".visit_id")
            .select("advertisements.title as advertisement_title", "COUNT(advertisements.id) as total_accesses")
            .group("advertisements.title")
        }
 
   #Validation
 