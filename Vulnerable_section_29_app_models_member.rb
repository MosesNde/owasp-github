# typed: false
 class Member < User
   has_many :advertisements, class_name: "Advertisements"
 