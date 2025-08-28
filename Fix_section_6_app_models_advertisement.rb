 # typed: false
 class Advertisement < ApplicationRecord
   extend T::Sig
  SEARCH_ATTRIBUTES = %i[title description]

   belongs_to :category, counter_cache: :advertisements_count
   belongs_to :user
   visitable :ahoy_visit
             .group("advertisements.title")
         }
 
  scope :search_for, ->(query) {
          sql_query = SEARCH_ATTRIBUTES.map { |att| "#{att} ~~* '%#{query}%'" }.join " OR "
          before_finish_date.where(sql_query)
        }
   #Validation
 
   sig { returns(T::Boolean) }