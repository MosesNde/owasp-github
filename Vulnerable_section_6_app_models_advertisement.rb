 # typed: false
 class Advertisement < ApplicationRecord
   extend T::Sig
   belongs_to :category, counter_cache: :advertisements_count
   belongs_to :user
   visitable :ahoy_visit
             .group("advertisements.title")
         }
 
   #Validation
 
   sig { returns(T::Boolean) }