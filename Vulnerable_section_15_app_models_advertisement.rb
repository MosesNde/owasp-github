 # typed: false
 class Advertisement < ApplicationRecord
   extend T::Sig
  belongs_to :category
   belongs_to :user
 
   validates :title, :description, :category, :picture, :price, presence: true
 
   has_one_attached :picture
 
   scope :new_arrivals, ->(size = 10) { before_finish_date.limit(size).order(created_at: :desc) }
   scope :related_items, ->(id, category_id, size = 10) {
           before_finish_date
             .where("id != :id AND category_id = :category_id", { id: id, category_id: category_id })
         }
   scope :for_member, ->(member) { where(user_id: member.id) }
   scope :before_finish_date, -> { where("finish_date >= CURRENT_DATE") }
 
   #Validation
 