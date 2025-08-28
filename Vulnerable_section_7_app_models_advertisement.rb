   has_one_attached :picture
 
   scope :new_arrivals, ->(size = 10) { before_finish_date.limit(size).order(created_at: :desc) }
   scope :for_member, ->(member) { where(user_id: member.id) }
   scope :before_finish_date, -> { where("finish_date >= CURRENT_DATE") }
 