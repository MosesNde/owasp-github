# typed: true
 class AdminPolicy < UserPolicy
   extend T::Sig
 
 
   class Scope < ApplicationPolicy::Scope
     def resolve
      Admin.left_outer_joins(:roles).select(:id, :name, :email).distinct.order(:name)
     end
   end
 end